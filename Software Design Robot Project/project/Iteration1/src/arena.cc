/**
 * @file arena.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <math.h>
#include <algorithm>
#include <iostream>
#include "src/arena.h"
#include "src/robot.h"
#include "src/obstacle.h"
#include "src/event_collision.h"
#include "src/arena_params.h"
#include "src/recharge_station.h"
#include "src/home_base.h"
#include "src/event_recharge.h"
#include "src/event_command.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Arena::Arena(const struct arena_params* const params) :
  x_dim_(params->x_dim - 200), y_dim_(params->y_dim),
  n_robots_(1),
  n_obstacles_(params->n_obstacles),
  robot_(new Robot(&params->robot)),
  recharge_station_(new RechargeStation(params->recharge_station.radius,
    params->recharge_station.pos,
    params->recharge_station.color)),
  home_base_(new HomeBase(&params->home_base)),
  entities_(),
  mobile_entities_() {
  batterylevel = robot_->battery_level();
  wins = 0;
  loss = 0;
  robot_->heading_angle(90);
  home_base_->set_ent_Num(1);
  robot_->set_ent_Num(2);
  entities_.push_back(robot_);
  mobile_entities_.push_back(robot_);
  entities_.push_back(recharge_station_);
  entities_.push_back(home_base_);
  mobile_entities_.push_back(home_base_);

  for (size_t i = 0; i < n_obstacles_; ++i) {
    entities_.push_back(new Obstacle(
        params->obstacles[i].radius,
        params->obstacles[i].pos,
        params->obstacles[i].color));
  } /* for(i..) */
}

Arena::~Arena(void) {
  for (auto ent : entities_) {
    delete ent;
  } /* for(ent..) */
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void Arena::Reset(void) {
  for (auto ent : entities_) {
    ent->Reset();
  } /* for(ent..) */
} /* reset() */

std::vector<Obstacle*> Arena::obstacles(void) {
  std::vector<Obstacle*> res;
  for (auto ent : entities_) {
    Obstacle* o = dynamic_cast<Obstacle*>(ent);
    if (o) {
      res.push_back(o);
    }
  } /* for(ent..) */
  return res;
} /* robots() */

void Arena::AdvanceTime(double dt) {
  for (size_t i = 0; i < 1; ++i) {
    UpdateEntitiesTimestep();
  } /* for(i..) */
} /* AdvanceTime() */

void Arena::UpdateEntitiesTimestep(void) {
  /*
   * First, update the position of all entities, according to their current
   * velocities.
   */
  for (auto ent : entities_) {
    ent->TimestepUpdate(1);
  } /* for(ent..) */

  set_battery_level(robot_->battery_level());

  /*
   * Next, check if the robot has run out of battery
   */

  if (robot_->battery_level() <=0 && robot_->get_speed() > 0) {
    robot_->set_speed(0);
    enum event_commands cmd = COM_STOP;
    loss++;
    EventCommand event(cmd);
    robot_->Accept(&event);
    home_base_->Stop();
  }

  /*
   * Next, check if the robot has collided with the recharge station or the home
   * base. These need to be before the general collisions, which can move the
   * robot away from these "obstacles" before the "collisions" have been
   * properly processed.
   *
   * Note: collision with the recharge station will recharge the battery of the
   * robot and collision with the home base will end the game
   */

  EventCollision ec;
  CheckForEntityCollision(robot_, home_base_, &ec, robot_->collision_delta());
  if (ec.collided()) {
    enum event_commands command_stop = COM_STOP;
    EventCommand event(command_stop);
    robot_->Accept(&event);
    wins++;
    robot_->set_speed(0);
    home_base_->Stop();
  }

  CheckForEntityCollision(robot_, recharge_station_, &ec,
                          robot_->collision_delta());
  if (ec.collided()) {
    EventRecharge er;
    robot_->Accept(&er);
  }

  /*
   * Finally, some pairs of entities may now be close enough to be considered
   * colliding, send collision events as necessary.
   *
   * When something collides with an immobile entity, the immobile entity does
   * not move (duh), so no need to send it a collision event.
   */
  for (auto ent : mobile_entities_) {
    // Check if it is out of bounds. If so, use that as point of contact.
    CheckForEntityOutOfBounds(ent, &ec);

    // If not at wall, check if it is colliding with any other entities (not
    // itself)
    if (!ec.collided()) {
      for (size_t i = 0; i < entities_.size(); ++i) {
        if (entities_[i] == ent) {
          continue;
        }
        CheckForEntityCollision(ent, entities_[i], &ec, ent->collision_delta());
        if (ec.collided()) {
          break;
        }
      } /* for(i..) */
    } /* else */
    ent->Accept(&ec);
  } /* for(ent..) */
} /* UpdateEntities() */



void Arena::CheckForEntityOutOfBounds(const ArenaMobileEntity * const ent,
                                     EventCollision * const event) {
  // Angle of reflection should be 180-heading for walls
  // Right Wall
  if (ent->get_ent_Num() == 1) {  // Right Wall
    if (ent->get_pos().x() + ent->radius() >= x_dim_) {
      event->collided(true);
      event->point_of_contact(Position(x_dim_, ent->get_pos().y()));
      event->angle_of_contact(360 -  ent->heading_angle());
    } else if (ent->get_pos().x() - ent->radius() <= 0) {  // Left Wall
      event->collided(true);
      event->point_of_contact(Position(0, ent->get_pos().y()));
      event->angle_of_contact(360 - ent->heading_angle());
    } else if (ent->get_pos().y() + ent->radius() >= y_dim_) {  // Bottom Wall
      event->collided(true);
      event->point_of_contact(Position(ent->get_pos().x(), y_dim_));
      event->angle_of_contact(180 - ent->heading_angle());
    } else if (ent->get_pos().y() - ent->radius() <= 0) {  // Top Wall
      event->collided(true);
      event->point_of_contact(Position(ent->get_pos().x(), 0));
      event->angle_of_contact(180 - ent->heading_angle());
    } else {
      event->collided(false);
    }
  } else {  // Right Wall
  if (ent->get_pos().x() + ent->radius() >= x_dim_) {
    event->collided(true);
    event->point_of_contact(Position(x_dim_, ent->get_pos().y()));
    event->angle_of_contact(ent->heading_angle() - 180);
  } else if (ent->get_pos().x() - ent->radius() <= 0) {  // Left Wall
    event->collided(true);
    event->point_of_contact(Position(0, ent->get_pos().y()));
    event->angle_of_contact(ent->heading_angle() - 180);
  } else if (ent->get_pos().y() + ent->radius() >= y_dim_) {  // Bottom Wall
    event->collided(true);
    event->point_of_contact(Position(ent->get_pos().x(), y_dim_));
    event->angle_of_contact(ent->heading_angle());
  } else if (ent->get_pos().y() - ent->radius() <= 0) {  // Top Wall
    event->collided(true);
    event->point_of_contact(Position(ent->get_pos().x(), 0));
    event->angle_of_contact(ent->heading_angle());
  } else {
    event->collided(false);
  }
}
} /* entity_out_of_bounds() */

void Arena::CheckForEntityCollision(const ArenaMobileEntity* const ent1,
  const ArenaEntity* const ent2, EventCollision * const event,
  double collision_delta) {
  /* Note: this assumes circular entities */
  double ent1_x = ent1->get_pos().x();
  double ent1_y = ent1->get_pos().y();
  double ent2_x = ent2->get_pos().x();
  double ent2_y = ent2->get_pos().y();
  double dist = std::sqrt(std::pow(ent2_x - ent1_x, 2) +
                          std::pow(ent2_y - ent1_y, 2));

  if (dist > ent1->radius() + ent2->radius() + collision_delta) {
    event->collided(false);
  } else {
    double dif_x = ent1_x - ent2_x;
    double dif_y = ent1_y - ent2_y;
    double theta = atan(dif_y/dif_x);
    double pi = 3.141592653589;
    double conversion_to_degrees = 180/pi;
    double angle = theta * conversion_to_degrees;
    event->point_of_contact(Position((ent2->radius() * cos(theta) + ent2_x),
                            ((-1) * ent2->radius() * sin(theta) + ent2_y)));
    if (angle > 360) { angle -= 360; }
    if (angle < 0) { angle += 360; }


    if (ent1->get_ent_Num() == 1) {
      if (angle > 0 && angle <= 90 && dif_x >= 0) {
        event->angle_of_contact(270 - angle);
      } else if (angle > 270 && angle <= 360 && dif_y >= 0) {
        event->angle_of_contact(270 - angle);
      } else if (angle > 0 && angle <= 90 && dif_x < 0) {
        event->angle_of_contact(angle);
      } else if (angle > 270 && angle <= 360 && dif_y < 0) {
        event->angle_of_contact(90 - angle);
      } else if (static_cast<int>(angle+0.01) == 90 && dif_y > 0) {
        event->angle_of_contact(270);
      } else if (static_cast<int>(angle+0.01) == 270 && dif_y < 0) {
        event->angle_of_contact(90);
      } else if (static_cast<int>(angle+0.01) == 0 && dif_y > 0) {
        event->angle_of_contact(180);
      } else if (static_cast<int>(angle+0.01) == 180 && dif_y > 0) {
        event->angle_of_contact(0);
      }
    }

  if (ent1->get_ent_Num() == 2) {
    if (angle > 0 && angle <= 90 && dif_x >= 0) {
      event->angle_of_contact(180 - (angle - 180));
    } else if (angle > 270 && angle <= 360 && dif_y >= 0) {
      event->angle_of_contact(180 - angle);
    } else if (angle > 0 && angle <= 90 && dif_x < 0) {
      event->angle_of_contact(180 - angle);
    } else if (angle > 270 && angle <= 360 && dif_y < 0) {
      event->angle_of_contact(180 - (angle - 180));
    } else if (static_cast<int>(angle+0.01) == 90 && dif_y > 0) {
      event->angle_of_contact(270);
    } else if (static_cast<int>(angle+0.01) == 270 && dif_y < 0) {
      event->angle_of_contact(90);
    } else if (static_cast<int>(angle+0.01) == 0 && dif_y > 0) {
      event->angle_of_contact(180);
    } else if (static_cast<int>(angle+0.01) == 180 && dif_y > 0) {
      event->angle_of_contact(0);
    }
  }
    event->collided(true);
    if (ent1->get_ent_Num() == 1) {
      home_base_->Accept(event);
    } else if (ent1->get_ent_Num() == 2) {
      robot_->Accept(event);
    }
  }
} /* entities_have_collided() */

void Arena::Accept(const EventKeypress * const e) {
  enum event_commands cmd = e->get_command();
  EventCommand ev(cmd);
  robot_->Accept(&ev);
}

NAMESPACE_END(csci3081);
