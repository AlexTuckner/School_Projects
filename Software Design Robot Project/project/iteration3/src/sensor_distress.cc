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
#include "src/sensor_distress.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

void SensorDistress::Accept(const EventDistressCall * const e) {
  // Determine if the sensor should be activated or inactivated.
  if (e->get_is_frozen()) {
    this->set_is_activated(true);
  } else {
    this->set_is_activated(false);
  }
}

void SensorDistress::Reset(void) {
  this->set_is_activated(false);
} /* reset() */

NAMESPACE_END(csci3081);
