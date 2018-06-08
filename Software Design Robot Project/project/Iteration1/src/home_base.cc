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
     ArenaMobileEntity(params->radius, params->collision_delta,
     params->pos, params->color),
     sensor_touch_home() {
     heading = 260;
     heading_angle(heading);
     srand(time(NULL));
     set_speed(10);
     set_ent_Num(1);
     initial_position = params->pos;
     initial_heading_angle = heading;
  }
void HomeBase::TimestepUpdate(uint dt) {
     if (sensor_touch_home.activated()) {
       set_pos(get_Last_Position());
     } else {
     set_Second_Last_Position(get_Last_Position());
     set_Last_Position(get_pos());
     }

     randvalue = (rand() % 100) + 1;

     Position new_pos = this->get_pos();
     Position old_pos = this->get_pos();

     if (randvalue > 3) {
     // Movement is always along the heading_angle (i.e. the hypotenuse)
     new_pos.x(new_pos.x() + cos(this->heading_angle()*M_PI/180.0)*
               this->get_speed()*dt);
     new_pos.y(new_pos.y() + sin(this->heading_angle()*M_PI/180.0)*
               this->get_speed()*dt);
     this->set_pos(new_pos);
    } else {
      randangle = rand() % 360;
      this->heading_angle(randangle);
      new_pos.x(new_pos.x() + cos(this->heading_angle()*M_PI/180.0)*
                this->get_speed()*dt);
      new_pos.y(new_pos.y() + sin(this->heading_angle()*M_PI/180.0)*
                this->get_speed()*dt);
      this->set_pos(new_pos);
    }
  }

  void HomeBase::Accept(const EventCollision * const e) {
    sensor_touch_home.Accept(e);
    if (sensor_touch_home.activated()) {
    heading_angle(sensor_touch_home.angle_of_contact() - 180);
    }
  }

  void HomeBase::Reset(void) {
    speed = 10;
    this->set_pos(initial_position);
    this->heading_angle(initial_heading_angle);
  }


NAMESPACE_END(csci3081);
