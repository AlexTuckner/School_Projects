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
#include "src/robot.h"
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
Robot::Robot(const struct robot_params* const params) :
     ArenaMobileEntity(params->radius, kRobot, params->collision_delta,
     params->pos, params->color),
     sensor_touch_robot_(kRobot, 0, Position(0, 0), 0),
     sensor_distress_robot_(kRobot, 0, 10),
     sensor_entity_type_robot_(kRobot, 0, 10),
     sensor_proximity_robot_(kRobot, 0, 50, 90),
     motion_handler_robot_(290.0, 7.0),
     default_speed_(7.0) {
     initial_position_ = params->pos;
  }
void Robot::TimestepUpdate(uint dt) {
     if (sensor_touch_robot_.get_is_activated()) {
       set_pos(get_Last_Position());
       motion_handler_robot_.AcceptCollision(sensor_touch_robot_);
       sensor_touch_robot_.set_is_activated(false);
     } else if (get_speed() > 0) {
     set_Second_Last_Position(get_Last_Position());
     set_Last_Position(get_pos());
     }

     if (sensor_proximity_robot_.get_is_activated()) {
       motion_handler_robot_.AcceptProximity(sensor_proximity_robot_);
       sensor_proximity_robot_.set_is_activated(false);
       sensor_proximity_robot_.set_left(false);
       sensor_proximity_robot_.set_right(false);
       if (get_speed() - 2 < 3) {
         set_speed(3);
       } else {
         set_speed(get_speed() - 2);
       }
     } else {
       set_speed(get_default_speed());
     }


     if (sensor_distress_robot_.get_is_activated()) {
       set_speed(0);
     } else {
       set_speed(get_default_speed());
     }


     Position new_pos = this->get_pos();
     Position old_pos = this->get_pos();

     // Movement is always along the heading_angle (i.e. the hypotenuse)
     new_pos.set_x(new_pos.get_x() +
                  cos(motion_handler_robot_.get_heading_angle()
                  *M_PI/180.0)*this->get_speed()*dt);
     new_pos.set_y(new_pos.get_y() +
                  sin(motion_handler_robot_.get_heading_angle()
                  *M_PI/180.0)*this->get_speed()*dt);
     this->set_pos(new_pos);
  }

  void Robot::Accept(const EventCollision * const e) {
  //   sensor_touch_robot_.Accept(e);
  //   if (sensor_touch_robot_.get_is_activated()) {
  //   set_heading_angle(sensor_touch_robot_.get_angle_of_contact()); //- 180);
  //   }
  }

  void Robot::Stop() {
    motion_handler_robot_.Stop();
  }

  void Robot::Reset(void) {
    motion_handler_robot_.Reset();
    sensor_distress_robot_.Reset();
    this->set_pos(this->get_initial_position());
    set_speed(get_default_speed());
  }


NAMESPACE_END(csci3081);
