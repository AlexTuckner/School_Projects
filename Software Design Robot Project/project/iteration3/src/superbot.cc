/**
 * @file obstacle.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "src/superbot.h"
#include "src/entity_type.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Static Variables
 ******************************************************************************/

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
SuperBot::SuperBot(const struct robot_params* const params,
        Position p, double heading_angle) :
     ArenaMobileEntity(params->radius, kSuperBot, params->collision_delta,
     p, params->color),
     sensor_touch_superbot_(kSuperBot, 0, p, 0),
     sensor_entity_type_superbot_(kRobot, 0, 10),
     sensor_proximity_superbot_(kRobot, 0, 60, 90),
     motion_handler_superbot_(heading_angle, 8.5),
     default_speed_(8.5) {
       set_pos(p);
       set_heading_angle(heading_angle);
       set_Last_Position(p);
       csci3081::Color c(255, 255, 22, 255);
       set_color(c);
     }

void SuperBot::TimestepUpdate(uint dt) {
     if (sensor_touch_superbot_.get_is_activated()) {
       set_pos(get_Last_Position());
       motion_handler_superbot_.AcceptCollision(sensor_touch_superbot_);
       sensor_touch_superbot_.set_is_activated(false);
     } else if (get_speed() > 0) {
     set_Second_Last_Position(get_Last_Position());
     set_Last_Position(get_pos());
     }

     if (sensor_proximity_superbot_.get_is_activated()) {
       motion_handler_superbot_.AcceptProximity(sensor_proximity_superbot_);
       sensor_proximity_superbot_.set_is_activated(false);
       sensor_proximity_superbot_.set_left(false);
       sensor_proximity_superbot_.set_right(false);
       if (get_speed() - 2 < 3) {
         set_speed(3);
       } else {
         set_speed(get_speed() - 2);
       }
     } else {
       set_speed(get_default_speed());
     }


     Position new_pos = this->get_pos();
     Position old_pos = this->get_pos();

     // Movement is always along the heading_angle (i.e. the hypotenuse)
     new_pos.set_x(new_pos.get_x() +
                  cos(motion_handler_superbot_.get_heading_angle()*
                  M_PI/180.0)*this->get_speed()*dt);
     new_pos.set_y(new_pos.get_y() +
                  sin(motion_handler_superbot_.get_heading_angle()*
                  M_PI/180.0)*this->get_speed()*dt);
     this->set_pos(new_pos);
  }

  void SuperBot::Accept(const EventCollision * const e) {
    // sensor_touch_superbot_.Accept(e);
    // if (sensor_touch_superbot_.get_is_activated()) {
    // set_heading_angle(sensor_touch_superbot_.get_angle_of_contact());
    // }
  }

  void SuperBot::Stop() {
    motion_handler_superbot_.Stop();
  }

  void SuperBot::Reset(void) {
    motion_handler_superbot_.Reset();
    this->set_pos(this->get_initial_position());
  }


NAMESPACE_END(csci3081);
