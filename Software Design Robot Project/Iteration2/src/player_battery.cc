/**
 * @file player_battery.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/player_battery.h"
#include <math.h>
#include <cmath>
#include <iostream>

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
double PlayerBattery::Deplete(Position old_pos, Position new_pos, double dt) {
  /* Deplete battery by some value based on movement and speed */
  double dist = std::sqrt(std::pow(new_pos.get_x() - old_pos.get_x(), 2) +
                           std::pow(new_pos.get_y() - old_pos.get_y(), 2));
  if (dist > 0) {
    charge_ -= dist * kLINEAR_SCALE_FACTOR;
    charge_ -= kBASE_DEPLETION;
  }
  if (charge_ < 0) {
    charge_ = 0;
  }

  return charge_;
} /* deplete() */

void PlayerBattery::Accept(const EventCollision * const e) {
  /* Deplete battery by some value -- arbitrary selected for bumping */
  charge_ -= 2.5;
}



NAMESPACE_END(csci3081);
