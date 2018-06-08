/**
 * @file motion_handler_player.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include "src/common.h"
#include "src/motion_handler_player.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
MotionHandlerPlayer::MotionHandlerPlayer(double heading, double speed) :
  MotionHandler(heading, speed) {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
// Takes in the arrowkey commands from the user and reacts accordingly
void MotionHandlerPlayer::AcceptCommand(enum event_commands cmd) {
  switch (cmd) {
  case COM_TURN_LEFT: set_heading_angle(get_heading_angle() - 30); break;
  case COM_TURN_RIGHT: set_heading_angle(get_heading_angle() + 30); break;
  case COM_SPEED_UP:
    if (get_speed() + 3 < get_max_speed()) {
      set_speed(get_speed() + 3);
    } else {
      set_speed(get_max_speed());
    }
  break;
  case COM_SLOW_DOWN:
  if (get_speed() - 5 >= 0) {
    set_speed(get_speed() - 5);
  } else {
    set_speed(0);
  }
  break;
  case COM_STOP:
    set_max_speed(0);
    break;
  default:
    std::cerr << "FATAL: bad actuator command" << std::endl;
    assert(0);
  } /* switch() */
} /* accept_command() */

void MotionHandlerPlayer::AcceptCollision(SensorTouch st) {
  set_heading_angle(st.get_angle_of_contact());
}
// Update the velocity if sensor touch is activated
void MotionHandlerPlayer::UpdateVelocity(SensorTouch st) {
  if (st.get_is_activated()) {
    if (get_speed() > 3) {
      set_speed(get_speed() - 2);
    } else if (get_speed() == 0) {
    } else {
      set_speed(1);
    }
  }
}



NAMESPACE_END(csci3081);
