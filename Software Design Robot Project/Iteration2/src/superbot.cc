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
SuperBot::SuperBot(const struct robot_params* const params) :
     ArenaMobileEntity(params->radius, kSuperBot, params->collision_delta,
     params->pos, params->color),
     sensor_touch_superbot_(kSuperBot, 0, Position(0, 0), 0),
     sensor_distress_superbot_(kRobot, 0, 10),
     sensor_entity_type_superbot_(kRobot, 0, 10),
     sensor_proximity_superbot_(kRobot, 0, 10, 60),
     motion_handler_superbot_(340.0, 10.0) {
     initial_position_ = params->pos;
  }
void SuperBot::TimestepUpdate(uint dt) {
     if (sensor_touch_superbot_.get_is_activated()) {
       set_pos(get_Last_Position());
     } else {
     set_Second_Last_Position(get_Last_Position());
     set_Last_Position(get_pos());
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
    sensor_touch_superbot_.Accept(e);
    if (sensor_touch_superbot_.get_is_activated()) {
    set_heading_angle(sensor_touch_superbot_.get_angle_of_contact());
    }
  }

  void SuperBot::Stop() {
    motion_handler_superbot_.Stop();
  }

  void SuperBot::Reset(void) {
    motion_handler_superbot_.Reset();
    this->set_pos(this->get_initial_position());
  }


NAMESPACE_END(csci3081);
