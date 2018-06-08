/**
 * @file sensor_touch.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <limits>
#include <iostream>
#include "src/sensor_touch.h"
#include "src/arena_entity.h"
#include "src/motion_handler_player.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

void SensorTouch::Accept(const EventCollision * const e) {
  // Determine if the sensor should be activated or inactivated.
  if (e->get_collided()) {
    this->set_is_activated(true);
    point_of_contact_ = e->get_event_location();
    angle_of_contact_ = e->get_angle_of_contact();
  } else {
    this->set_is_activated(false);
  }
}

void SensorTouch::Reset(void) {
  this->set_is_activated(false);
} /* reset() */

NAMESPACE_END(csci3081);
