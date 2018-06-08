/**
 * @file motion_handler_player.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include "src/position.h"
#include "src/common.h"
#include "src/motion_handler_base.h"
/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
MotionHandler::MotionHandler(double heading, double speed) :
  speed_(speed),
  heading_angle_(heading),
  initial_speed_(speed),
  initial_heading_angle_(heading),
  max_speed_(30) {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/


// Reset the motion of the player when "Reset" is pressed
void MotionHandler::Reset(void) {
  set_heading_angle(initial_heading_angle_);
  set_speed(initial_speed_);
  set_max_speed(30);
}

NAMESPACE_END(csci3081);
