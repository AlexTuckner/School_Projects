/**
 * @file home_base.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_SUPERBOT_H_
#define SRC_SUPERBOT_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "src/robot_params.h"
#include "src/arena_mobile_entity.h"
#include "src/event_collision.h"
#include "src/event_command.h"
#include "src/motion_handler_robot.h"
#include "src/sensor_touch.h"
#include "src/sensor_distress.h"
#include "src/sensor_entity_type.h"
#include "src/sensor_proximity.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /**
  * \class SuperBot : public ArenaMobileEntity
  * Not fully implemented yet!
  * @brief A super-robot in which the player must avoid.
  * If a superbot touches the player it will stun the
  * player, preventing the player from winning the game.
  * The goal of the superbot is to prevent the player from colliding with the
  * other robots to prevent the player from winning.
  */
class SuperBot : public ArenaMobileEntity {
 public:
  explicit SuperBot(const struct robot_params* const params);

  /**
   * \fn void TimestepUpdate(unsigned int dt) override;
   * @brief Update the superbot's position and velocity after the specified
   * duration has passed.
   *
   * @param dt The # of timesteps that have elapsed since the last update.
   */
  void TimestepUpdate(unsigned int dt) override;

  /**
   * \fn void Accept(const EventCollision * const e) override;
   * @brief  Pass along a collision event (from arena) to the touch sensor.
   *
   * This method provides a framework in which sensors can get different types
   * of information from different sources. The robot's heading will be updated
   * to move it away from the incident angle at the point of contact.
   *
   * @param e The collision event.
   */
  void Accept(const EventCollision * const e) override;

  /**
   * \fn void Reset(void) override
   * @brief Reset the superbot to a newly constructed state (needed for reset
   * button to work in arena GUI).
   */
  void Reset(void) override;

  /**
  * \fn void Stop(void);
  * @brief Stop the entity from moving
  * For example, if the game ends
  */
  void Stop(void);

  double get_heading_angle(void) const override {
    return motion_handler_superbot_.get_heading_angle();
  }
  void set_heading_angle(double ha) override {
    motion_handler_superbot_.set_heading_angle(ha);
  }
  double get_speed(void) const override {
    return motion_handler_superbot_.get_speed();
  }
  void set_speed(double sp) override { motion_handler_superbot_.set_speed(sp); }

  std::string get_name(void) const override { return "SuperBot"; }

  Position get_initial_position() {return initial_position_;}

 private:
  SensorTouch sensor_touch_superbot_;
  SensorProximity sensor_proximity_superbot_;
  SensorDistress sensor_distress_superbot_;
  SensorEntityType sensor_entity_type_superbot_;
  MotionHandlerRobot motion_handler_superbot_;
  Position initial_position_;
};

NAMESPACE_END(csci3081);

#endif /* SRC_SUPERBOT_H_ */
