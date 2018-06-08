/**
 * @file robot_motion_handler.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/robot_motion_handler.h"
#include <iostream>

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
RobotMotionHandler::RobotMotionHandler() :
  heading_angle_(30),
  speed_(5),
  max_speed_(30) {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
// Takes in the arrowkey commands from the user and reacts accordingly
void RobotMotionHandler::AcceptCommand(enum event_commands cmd) {
  switch (cmd) {
  case COM_TURN_LEFT: heading_angle(heading_angle() - 30); break;
  case COM_TURN_RIGHT: heading_angle(heading_angle() + 30); break;
  case COM_SPEED_UP:
    if (speed() + 3 < max_speed()) {
      speed(speed() + 3);
    } else {
      speed(max_speed());
    }
  break;
  case COM_SLOW_DOWN:
  if (speed() - 5 >= 0) {
    speed(speed() - 5);
  } else {
    speed(0);
  }
  break;
  case COM_STOP:
    max_speed(0);
    break;
  default:
    std::cerr << "FATAL: bad actuator command" << std::endl;
    assert(0);
  } /* switch() */
} /* accept_command() */

// Update the velocity if sensor touch is activated
void RobotMotionHandler::UpdateVelocity(SensorTouch st) {
  if (st.activated()) {
    heading_angle_ = - st.angle_of_contact();
  }
}

// Reset the motion of the robot when "Reset" is pressed
void RobotMotionHandler::Reset(void) {
  heading_angle(90);
  speed(5);
  max_speed(30);
}

NAMESPACE_END(csci3081);
