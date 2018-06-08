/**
 * @file player.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_PLAYER_H_
#define SRC_PLAYER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "src/motion_handler_player.h"
#include "src/player_motion_behavior.h"
#include "src/sensor_touch.h"
#include "src/player_battery.h"
#include "src/arena_mobile_entity.h"
#include "src/event_recharge.h"
#include "src/event_collision.h"
#include "src/event_command.h"
#include "src/entity_type.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * \class class Player : public ArenaMobileEntity
 * @brief Class representing a mobile player within the arena.
 *
 * Players have the capability of updating their own position when asked, and
 * also track their own velocity and heading. They have a touch sensor for
 * responding to collision events which is activated/deactivated on collision
 * events.
 *
 */
class Player : public ArenaMobileEntity {
 public:
  explicit Player(const struct player_params* const params);

  /**
   * /fn void ResetBattery(void)
   * @brief Reset the player's battery to full after an encounter with the
   * recharge station.
   */
  void ResetBattery(void);

  /**
   * \fn void Reset(void) override
   * @brief Reset the player to a newly constructed state (needed for reset
   * button to work in arena GUI).
   */
  void Reset(void) override;

  /**
   * \fn void TimestepUpdate(unsigned int dt) override;
   * @brief Update the player's position and velocity after the specified
   * duration has passed.
   *
   * @param dt The # of timesteps that have elapsed since the last update.
   */
  void TimestepUpdate(unsigned int dt) override;

  /**
   * \fn void Accept(const EventRecharge * const e)
   * @brief Accept a recharge event.
   *
   * This causes the player's battery to become fully charged.
   *
   * @param e The recharge event.
   */
  void Accept(const EventRecharge * const e);

  /**
   * \fn void Accept(const EventCollision * const e) override;
   * @brief  Pass along a collision event (from arena) to the touch sensor.
   *
   * This method provides a framework in which sensors can get different types
   * of information from different sources. The player's heading will be updated
   * to move it away from the incident angle at the point of contact.
   *
   * @param e The collision event.
   */
  void Accept(const EventCollision * const e) override;

  /**
   * \fn void Accept(const EventCommand * const e)
   * @brief  Pass along an Event Command from the arena to motion handler.
   *
   */
  void Accept(const EventCommand * const e);

  /**
   * \fn void EventCmd(enum event_commands cmd)
   * @brief Handle user input commands to change the heading or speed.
   *
   * @param cmd The command to process.
   */
  void EventCmd(enum event_commands cmd);

  /**
   * \fn double battery_level(void)
   * @brief Get the current battery level of the player.
   */
  double get_battery_level(void) { return battery_.get_level(); }
  double get_heading_angle(void) const override {
    return motion_handler_player_.get_heading_angle();
  }
  void set_heading_angle(double ha) override {
    motion_handler_player_.set_heading_angle(ha);
  }
  double get_speed(void) const override {
    return motion_handler_player_.get_speed();
  }
  void set_speed(double sp) override { motion_handler_player_.set_speed(sp); }
  int get_ent_Num() const {return ent_Num;}
  void set_ent_Num(int n) {ent_Num = n;}
  Position get_initial_Pos() {return initial_pos;}
  void set_initial_Pos(Position p) { initial_pos = p;}
  std::string get_name(void) const override {
    return "Player";
  }
  void set_frozen(bool b) {frozen = b;}
  bool get_frozen() {return frozen;}
  void set_frozen_time(int f) {frozen_time = f;}
  int get_frozen_time() {return frozen_time;}
  void decrement_frozen_time() {frozen_time--;}
  SensorTouch* get_sensor_t() {return &sensor_touch_;}

 private:
  static unsigned int next_id_;

  int id_;
  PlayerBattery battery_;
  MotionHandlerPlayer motion_handler_player_;
  PlayerMotionBehavior player_motion_behavior_;
  SensorTouch sensor_touch_;
  int ent_Num = 2;
  Position initial_pos;
  bool frozen;
  int frozen_time;
};

NAMESPACE_END(csci3081);

#endif /* SRC_PLAYER_H_ */
