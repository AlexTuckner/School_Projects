/**
 * @file obstacle.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/home_base.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
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
HomeBase::HomeBase(const struct home_base_params* const params) :
  ArenaMobileEntity(params->radius, kHomeBase, params->collision_delta,
  params->pos, params->color),
  sensor_touch_home(kHomeBase, 0, Position(0, 0), 0),
  motion_handler_home_(210.0, 10.0) {
  srand(time(NULL));
  initial_position_ = params->pos;
  }

void HomeBase::TimestepUpdate(uint dt) {
     if (sensor_touch_home.get_is_activated()) {
       set_pos(get_Last_Position());
       motion_handler_home_.AcceptCollision(sensor_touch_home);
       sensor_touch_home.set_is_activated(false);
     } else {
     set_Second_Last_Position(get_Last_Position());
     set_Last_Position(get_pos());
     }

     randvalue = (rand() % 100) + 1;

     Position new_pos = this->get_pos();
     Position old_pos = this->get_pos();

     if (randvalue > 3) {
     // Movement is always along the heading_angle (i.e. the hypotenuse)
     new_pos.set_x(new_pos.get_x() +
                  cos(motion_handler_home_.get_heading_angle()*M_PI/180.0)*
                  this->get_speed()*dt);
     new_pos.set_y(new_pos.get_y() +
                  sin(motion_handler_home_.get_heading_angle()*M_PI/180.0)*
                  this->get_speed()*dt);
     this->set_pos(new_pos);
   } else {
      randangle = rand() % 360;
      motion_handler_home_.set_heading_angle(randangle);
      new_pos.set_x(new_pos.get_x() +
                cos(motion_handler_home_.get_heading_angle()*M_PI/180.0)*
                this->get_speed()*dt);
      new_pos.set_y(new_pos.get_y() +
                sin(motion_handler_home_.get_heading_angle()*M_PI/180.0)*
                this->get_speed()*dt);
      this->set_pos(new_pos);
    }
  }

  void HomeBase::Accept(const EventCollision * const e) {}

  void HomeBase::Stop() {
    motion_handler_home_.Stop();
  }

  void HomeBase::Reset(void) {
    motion_handler_home_.Reset();
    this->set_pos(this->get_initial_position());
  }


NAMESPACE_END(csci3081);
