/**
 * @file player_battery.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_PLAYER_BATTERY_H_
#define SRC_PLAYER_BATTERY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/common.h"
#include "src/event_collision.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Classes
 ******************************************************************************/
/**
 * \class PlayerBattery
 * @brief The battery for a player.
 *  This class sets the depletion rates for the player battery
 */
class PlayerBattery {
 public:
  explicit PlayerBattery(double max_charge) : charge_(max_charge),
                                             max_charge_(max_charge) {}

  /**
   * \var double kBASE_DEPLETION = 0.1;
   * @brief All players consume SOME power, even when just sitting there not moving.
   */
  double kBASE_DEPLETION = 0.1;

  /**
   * \var double kLINEAR_SCALE_FACTOR = 0.01;
   * @brief The amount of energy consumed by the player due to its linear speed
   * its is directly proportional to that speed, with a scaling factor.
   */
  double kLINEAR_SCALE_FACTOR = 0.01;

  /**
   * \var double kANGULAR_SCALE_FACTOR = 0.01;
   * @brief The amount of energy consumed by the player due to its angular speed
   * its is directly proportional to that speed, with a scaling factor.
   */
  double kANGULAR_SCALE_FACTOR = 0.01;

  /**
   * \fn double level(void) const
   * @brief Get the current battery level.
   */
  double get_level(void) const { return charge_; }
  void hit_obect(void) {charge_ -= 2;}
  /**
   * \fn void EventRecharge(void)
   * @brief Handle a recharge event by instantly restoring the player's battery
   * to its maximum value.
   */
  void EventRecharge(void) { charge_ = max_charge_; }

  /**
   * \fn void Reset(void)
   * @brief Reset the player's battery to its newly constructed/undepleted state.
   */
  void Reset(void) { EventRecharge();}

  /**
   * \fn double Deplete(__unused Position old_pos,
     __unused Position new_pos, __unused double dt);
   * @brief Calculate the new battery level based on the current linear/angular speed.
   *
   * @param linear_vel The current linear speed, in m/s.
   * @param angular_vel The current angular speed, in rad/s.
   *
   * @return The updated battery level.
   */
  double Deplete(__unused Position old_pos,
    __unused Position new_pos, __unused double dt);

  // This is how the battery can be informed a collision occured.
  // Deplete accordingly.
  void Accept(const EventCollision * const e);

 private:
  double charge_;
  double max_charge_;
};

NAMESPACE_END(csci3081);

#endif  // SRC_player_battery_H_
