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
#include "src/motion_handler_home_base.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
MotionHandlerHomeBase::MotionHandlerHomeBase(double heading, double speed) :
  MotionHandler(heading, speed) {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

void MotionHandlerHomeBase::AcceptCollision(SensorTouch st) {
  set_heading_angle(st.get_angle_of_contact());
}

NAMESPACE_END(csci3081);
