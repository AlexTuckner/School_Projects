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
#include "src/arena_entity.h"
#include "src/motion_handler_player.h"
#include "src/sensor_proximity.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

void SensorProximity::Accept(const EventProximity * const e) {
  // Determine if the sensor should be activated or inactivated.
  if (e->get_in_range()) {
    this->set_is_activated(true);
    if (e->get_event_left()) {
      this->set_left(true);
    }
    if (e->get_event_right()) {
      this->set_right(true);
    }
  } else {
    this->set_is_activated(false);
  }
}

void SensorProximity::Reset(void) {
  this->set_is_activated(false);
} /* reset() */

NAMESPACE_END(csci3081);
