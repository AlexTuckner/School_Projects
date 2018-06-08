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
#include "src/player.h"
#include "src/obstacle.h"
#include "src/event_collision.h"
#include "src/arena_params.h"
#include "src/recharge_station.h"
#include "src/home_base.h"
#include "src/event_recharge.h"
#include "src/event_command.h"
#include "src/robot.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Arena::Arena(const struct arena_params* const params) :
  x_dim_(params->x_dim - 250), y_dim_(params->y_dim),
  n_players_(1),
  n_robots_(params->n_robots),
  n_obstacles_(params->n_obstacles),
  player_(new Player(&params->player)),
  recharge_station_(new RechargeStation(params->recharge_station.radius,
    params->recharge_station.pos,
    params->recharge_station.color)),
  home_base_(new HomeBase(&params->home_base)),
  entities_(),
  mobile_entities_(),
  robots_(),
  superbots_(),
  sensors_t_(),
  sensors_p_(),
  sensors_e_(),
  sensors_d_(),
  initial_params(params) {
  batterylevel = player_->get_battery_level();
  wins = 0;
  losses = 0;
  win = false;
  loss = false;
  i = 0;
  j = 0;
  r = 0;
  s = 0;
  deleted = 0;
  player_->set_heading_angle(90);
  home_base_->set_ent_Num(1);
  player_->set_ent_Num(2);
  entities_.push_back(player_);
  mobile_entities_.push_back(player_);
  entities_.push_back(recharge_station_);
  entities_.push_back(home_base_);
  mobile_entities_.push_back(home_base_);
  sensors_t_.push_back(player_->get_sensor_t());
  sensors_t_.push_back(home_base_->get_sensor_t());

  for (size_t k = 0; k < n_robots_; ++k) {
    Robot* n = new Robot(&params->robots[k]);
    entities_.push_back(n);
    mobile_entities_.push_back(n);
    robots_.push_back(n);
    sensors_t_.push_back(n->get_sensor_t());
    sensors_p_.push_back(n->get_sensor_p());
    sensors_d_.push_back(n->get_sensor_d());
    sensors_e_.push_back(n->get_sensor_e());
  }


  for (size_t k = 0; k < n_obstacles_; ++k) {
    entities_.push_back(new Obstacle(
        params->obstacles[k].radius,
        kObstacle,
        params->obstacles[k].pos,
        params->obstacles[k].color));
  } /* for(i..) */
}

Arena::~Arena(void) {
  for (auto ent : entities_) {
      Obstacle* o = dynamic_cast<Obstacle*>(ent);
      if (o) {
        o->reset_next_id();
      }
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
} /* players() */

std::vector<Robot*> Arena::robots(void) {
  std::vector<Robot*> rob;
  for (auto ent : entities_) {
    Robot* robo = dynamic_cast<Robot*>(ent);
    if (robo) {
      rob.push_back(robo);
    }
  } /* for(ent..) */
  return rob;
} /* players() */

std::vector<SuperBot*> Arena::superbots(void) {
  return superbots_;
} /* players() */

void Arena::AdvanceTime(double dt) {
  for (size_t k = 0; k < 1; ++k) {
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

  set_battery_level(player_->get_battery_level());

  /*
   * Next, check if the player has run out of battery
   */

  if (player_->get_battery_level() <=0 && losses ==  0) {
    losses++;
    loss = true;
  }

  if (robots_.size() == 0 && losses == 0) {
    losses++;
    loss = true;
  }

  int num_robots_frozen = 0;
  for (auto rob : robots_) {
    if (rob->get_sensor_d()->get_is_activated()) {
      num_robots_frozen++;
    }
  }
  if (num_robots_frozen == robots_.size()) {
    wins++;
    win = true;
  }

  i = 0;
  r = 0;
  j = 0;
  for (auto m_ent : mobile_entities_) {
    EventCollision ec(m_ent->get_entity_type(), m_ent->get_pos(),
                    m_ent->get_heading_angle());
    for (auto ent : entities_) {
      if (m_ent != ent) {
      CheckForEntityCollision(m_ent, ent, &ec, m_ent->get_collision_delta());
    }
    if (ec.get_collided()) {
      if (m_ent->get_entity_type() == kPlayer && ent->get_entity_type()
            == kRechargeStation) {
        EventRecharge er;
        player_->Accept(&er);
      }

      if (m_ent->get_entity_type() == kRobot && ent->get_entity_type()
            == kPlayer) {
        EventDistressCall ed(m_ent->get_entity_type(), m_ent->get_pos());
        ed.set_is_frozen(true);
        sensors_d_[r]->Accept(&ed);
      }

      if (m_ent->get_entity_type() == kPlayer && ent->get_entity_type()
          == kRobot) {
          Robot* rob = dynamic_cast<Robot*>(ent);
          if (rob) {
            EventDistressCall ed(rob->get_entity_type(), rob->get_pos());
            ed.set_is_frozen(true);
            sensors_d_[j-3]->Accept(&ed);
          }
      }

      if (m_ent->get_entity_type() == kRobot && (ent->get_entity_type()
          == kRobot || ent->get_entity_type() == kSuperBot)) {
        EventDistressCall ed(m_ent->get_entity_type(), m_ent->get_pos());
        ed.set_is_frozen(false);
        sensors_d_[r]->Accept(&ed);
      }

      if (m_ent->get_entity_type() == kPlayer && ent->get_entity_type()
              == kSuperBot) {
          Player* p = dynamic_cast<Player*>(m_ent);
          if (p) {
            p->set_frozen_time(20);
            p->set_frozen(true);
          }
      }

      if (m_ent->get_entity_type() == kRobot && ent->get_entity_type()
          == kHomeBase) {
        deleted++;
        Position current_pos = m_ent->get_pos();
        double heading_ang = ec.get_angle_of_contact();
        sensors_d_.erase(sensors_d_.begin() + r);
        sensors_p_.erase(sensors_p_.begin() + r);
        sensors_e_.erase(sensors_e_.begin() + r);
        sensors_t_.erase(sensors_t_.begin() + i);
        entities_.erase(entities_.begin() + i + 1);
        mobile_entities_.erase(mobile_entities_.begin()+i);
        robots_.erase(robots_.begin() + r);
        SuperBot* superbot_ = new SuperBot(&initial_params->robots[0],
            current_pos, heading_ang);
        superbots_.push_back(superbot_);
        entities_.push_back(superbot_);
        mobile_entities_.push_back(superbot_);
        sensors_t_.push_back(superbot_->get_sensor_t());
        sensors_p_.push_back(superbot_->get_sensor_p());
        sensors_e_.push_back(superbot_->get_sensor_e());
        i--;
      } else {
        sensors_t_[i]->Accept(&ec);
      }
      ec.set_collided(false);
    }  // For ent

    CheckForEntityOutOfBounds(m_ent, &ec);
    if (ec.get_collided()) {
      sensors_t_[i]->Accept(&ec);
      ec.set_collided(false);
    }
    j++;
  }
    i++;
    if (m_ent->get_entity_type() == kRobot) {
      r++;
    }
  }

  i = 0;
  for (auto rob : robots_) {
    EventProximity ep(rob->get_entity_type(), rob->get_pos());
    for (auto ent : entities_) {
      if (rob != ent && ent->get_entity_type() != kRobot) {
        CheckForObjectInProximity(rob, ent, &ep);
        if (ep.get_in_range() && ent->get_entity_type() == kHomeBase) {
          ep.set_in_range(false);
        }
        if (ep.get_in_range()) {
          sensors_p_[i]->Accept(&ep);
          ep.set_in_range(false);
        }
      }
    }

    r = 0;
    EventProximity robep(rob->get_entity_type(), rob->get_pos());
    for (auto robs : robots_) {
      if (rob != robs) {
        CheckForObjectInProximity(rob, robs, &robep);
        if (robep.get_in_range() && sensors_d_[r]->get_is_activated()) {
          robep.set_event_left(false);
          robep.set_event_right(false);
        }


        if (robep.get_in_range()) {
          sensors_p_[i]->Accept(&robep);
          robep.set_in_range(false);
        }
      }
      r++;
    }

  i++;
  }

  s = 0;
  r = 0;
    for (auto superbot : superbots_) {
      EventProximity ep(superbot->get_entity_type(), superbot->get_pos());
      for (auto ent : entities_) {
        if (superbot != ent && ent->get_entity_type() != kRobot) {
          CheckForObjectInProximity(superbot, ent, &ep);
          if (ep.get_in_range() && ent->get_entity_type() == kPlayer) {
            ep.set_in_range(false);
          }
          if (ep.get_in_range()) {
            sensors_p_[robots_.size()+s]->Accept(&ep);
            ep.set_in_range(false);
          }
        }
      }
      r = 0;
      EventProximity robep(superbot->get_entity_type(), superbot->get_pos());
      for (auto robs : robots_) {
        CheckForObjectInProximity(superbot, robs, &robep);
        if (robep.get_in_range() && sensors_d_[r]->get_is_activated()) {
          robep.set_in_range(false);
          }
        if (robep.get_in_range()) {
          sensors_p_[robots_.size()+s]->Accept(&robep);
          robep.set_in_range(false);
          }
        r++;
      }
      s++;
    }

    if (player_->get_frozen() && player_->get_frozen_time() > 0) {
      player_->decrement_frozen_time();
    } else if (player_->get_frozen() && player_->get_frozen_time() == 0) {
      player_->set_speed(7.0);
      player_->set_frozen(false);
    }
} /* UpdateEntities() */



void Arena::CheckForEntityOutOfBounds(const ArenaMobileEntity * const ent,
                                     EventCollision * const event) {
  if (ent->get_pos().get_x() + ent->get_radius() >= x_dim_) {
    event->set_collided(true);
    event->set_event_location(Position(x_dim_, ent->get_pos().get_y()));
    event->set_angle_of_contact(180 - ent->get_heading_angle());
  } else if (ent->get_pos().get_x() - ent->get_radius() <= 0) {  // Left Wall
    event->set_collided(true);
    event->set_event_location(Position(0, ent->get_pos().get_y()));
    event->set_angle_of_contact(180 - ent->get_heading_angle());
  } else if (ent->get_pos().get_y() + ent->get_radius() >= y_dim_) {  // Bottom
    event->set_collided(true);
    event->set_event_location(Position(ent->get_pos().get_x(), y_dim_));
    event->set_angle_of_contact(-ent->get_heading_angle());
  } else if (ent->get_pos().get_y() - ent->get_radius() <= 0) {  // Top Wall
    event->set_collided(true);
    event->set_event_location(Position(ent->get_pos().get_x(), 0));
    event->set_angle_of_contact(-ent->get_heading_angle());
  } else {
    event->set_collided(false);
  }
} /* entity_out_of_bounds() */

void Arena::CheckForEntityCollision(const ArenaMobileEntity* const ent1,
  const ArenaEntity* const ent2, EventCollision * const event,
  double collision_delta) {
  /* Note: this assumes circular entities */
  double ent1_x = ent1->get_pos().get_x();
  double ent1_y = ent1->get_pos().get_y();
  double ent2_x = ent2->get_pos().get_x();
  double ent2_y = ent2->get_pos().get_y();
  double dist = std::sqrt(std::pow(ent2_x - ent1_x, 2) +
                          std::pow(ent2_y - ent1_y, 2));

  if (dist > ent1->get_radius() + ent2->get_radius() + collision_delta) {
    event->set_collided(false);
  } else {
    double dif_x = ent1_x - ent2_x;
    double dif_y = ent1_y - ent2_y;
    double theta = atan(dif_y/dif_x);
    double pi = 3.141592653589;
    double conversion_to_degrees = 180/pi;
    double angle = theta * conversion_to_degrees;
    event->set_event_location(Position((ent2->get_radius() *
      cos(theta) + ent2_x), ((-1) * ent2->get_radius() * sin(theta) + ent2_y)));
    if (angle > 360) { angle -= 360; }
    if (angle < 0) { angle += 360; }

    if (angle > 0 && angle <= 90 && dif_x >= 0) {  // SE Quadrant
      event->set_angle_of_contact(angle);
    } else if (angle > 270 && angle <= 360 && dif_y >= 0) {  // SW Quadrant
      event->set_angle_of_contact(angle - 180);
    } else if (angle > 0 && angle <= 90 && dif_x < 0) {  // NW Quadrant
      event->set_angle_of_contact(angle - 180);
    } else if (angle > 270 && angle <= 360 && dif_y < 0) {  // NE Quadrant
      event->set_angle_of_contact(angle);
    } else if (static_cast<int>(angle+0.01) == 90 && dif_y > 0) {
      event->set_angle_of_contact(270);
    } else if (static_cast<int>(angle+0.01) == 270 && dif_y < 0) {
      event->set_angle_of_contact(90);
    } else if (static_cast<int>(angle+0.01) == 0 && dif_y > 0) {
      event->set_angle_of_contact(180);
    } else if (static_cast<int>(angle+0.01) == 180 && dif_y > 0) {
      event->set_angle_of_contact(0);
    }
    event->set_collided(true);
  }
} /* entities_have_collided() */

double Arena::Positive(int angle) {
  while (angle < 0) {
    angle += 360;
  }
  if (angle > 360) {
    angle = angle % 360;
  }
  return angle;
}

void Arena::CheckForObjectInProximity(const class Robot* const
  ent1, const class ArenaEntity* const ent2, EventProximity * const ep) {
    double deltaX = ent2->get_pos().get_x() - ent1->get_pos().get_x();
    double deltaY = ent2->get_pos().get_y() - ent1->get_pos().get_y();
    double dist = std::sqrt(std::pow(deltaX, 2) + std::pow(deltaY, 2));
    double radius = ent1->get_proximity_range() + ent2->get_radius();
    if (dist > radius) {
      ep->set_in_range(false);
    } else {
      int heading_angle_ = Positive(
        static_cast<int>(ent1->get_heading_angle()));
      double triangle_theta = Positive(static_cast<int>(
                        atan(radius/dist)*180/3.14));
      double distance_theta = Positive(static_cast<int>(
                        atan2(deltaY, deltaX)*180/3.14));
      double sensor_lower = heading_angle_ - ent1->get_proximity_fov()/2;
      double sensor_upper = heading_angle_ + ent1->get_proximity_fov()/2;
      double sensed_lower = distance_theta - triangle_theta;
      double sensed_upper = distance_theta + triangle_theta;
      double range1[2];
      double range2[2];
      if (sensor_lower > sensor_upper) {
        range1[0] = sensor_upper;
        range1[1] = sensor_lower;
      } else {
        range1[0] = sensor_lower;
        range1[1] = sensor_upper;
      }
      if (sensed_lower > sensed_upper) {
        range2[0] = sensed_upper;
        range2[1] = sensed_lower;
      } else {
        range2[0] = sensed_lower;
        range2[1] = sensed_upper;
      }

      if (range2[0] >= range1[0] && range2[0] <= range1[1]) {
        ep->set_event_right(true);
        ep->set_in_range(true);
      } else if (range2[1] >= range1[0] && range2[1] <= range1[1]) {
        ep->set_event_left(true);
        ep->set_in_range(true);
      } else {
        ep->set_in_range(false);
      }  /*else */
    }  /* Else */
  }  /*CheckForObjectInProximity*/

  void Arena::CheckForObjectInProximity(const class SuperBot* const
    ent1, const class ArenaEntity* const ent2, EventProximity * const ep) {
      double deltaX = ent2->get_pos().get_x() - ent1->get_pos().get_x();
      double deltaY = ent2->get_pos().get_y() - ent1->get_pos().get_y();
      double dist = std::sqrt(std::pow(deltaX, 2) + std::pow(deltaY, 2));
      double radius = ent1->get_proximity_range() + ent2->get_radius();
      if (dist > radius) {
        ep->set_in_range(false);
      } else {
        int heading_angle_ = Positive(
              static_cast<int>(ent1->get_heading_angle()));
        double triangle_theta = Positive(static_cast<int>(
                          atan(radius/dist)*180/3.14));
        double distance_theta = Positive(static_cast<int>(
                          atan2(deltaY, deltaX)*180/3.14));
        double sensor_lower = heading_angle_ - ent1->get_proximity_fov()/2;
        double sensor_upper = heading_angle_ + ent1->get_proximity_fov()/2;
        double sensed_lower = distance_theta - triangle_theta;
        double sensed_upper = distance_theta + triangle_theta;
        double range1[2];
        double range2[2];
        if (sensor_lower > sensor_upper) {
          range1[0] = sensor_upper;
          range1[1] = sensor_lower;
        } else {
          range1[0] = sensor_lower;
          range1[1] = sensor_upper;
        }
        if (sensed_lower > sensed_upper) {
          range2[0] = sensed_upper;
          range2[1] = sensed_lower;
        } else {
          range2[0] = sensed_lower;
          range2[1] = sensed_upper;
        }

        if (range2[0] >= range1[0] && range2[0] <= range1[1]) {
          ep->set_event_right(true);
          ep->set_in_range(true);
        } else if (range2[1] >= range1[0] && range2[1] <= range1[1]) {
          ep->set_event_left(true);
          ep->set_in_range(true);
        } else {
          ep->set_in_range(false);
        }  /*else */
      }  /* Else */
    }  /*CheckForObjectInProximity*/


void Arena::Accept(const EventKeypress * const e) {
  enum event_commands cmd = e->get_command();
  EventCommand ev(cmd);
  player_->Accept(&ev);
}

NAMESPACE_END(csci3081);
