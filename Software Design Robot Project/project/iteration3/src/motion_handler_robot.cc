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
#include "src/motion_handler_robot.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
MotionHandlerRobot::MotionHandlerRobot(double heading, double speed) :
  MotionHandler(heading, speed) {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

void MotionHandlerRobot::AcceptCollision(SensorTouch st) {
  set_heading_angle(st.get_angle_of_contact());
}

void MotionHandlerRobot::AcceptProximity(SensorProximity sp) {
  // This will force the robot to the left first if they are both activated
  if (sp.get_left()) {
    set_heading_angle(get_heading_angle() + 30);
  } else if (sp.get_right()) {
    set_heading_angle(get_heading_angle() - 30);
  }
}



NAMESPACE_END(csci3081);
