/**
 * @file home_base.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_ROBOT_H_
#define SRC_ROBOT_H_

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
 * \class Robot : public ArenaMobileEntity
 * @brief A robot in which the player must collide with all robots to win.
 * If a robot touches the homebase it becomes a superbot which can stun the
 * player, preventing the player from winning the game.  The goal of the robot
 * is to randomly collide with the homebase and turn to a superbot.
 */
class Robot : public ArenaMobileEntity {
 public:
  explicit Robot(const struct robot_params* const params);

  /**
   * \fn void TimestepUpdate(unsigned int dt) override;
   * @brief Update the robot's position and velocity after the specified
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
   * @brief Reset the robot to a newly constructed state (needed for reset
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
    return motion_handler_robot_.get_heading_angle();
  }
  void set_heading_angle(double ha) override {
    motion_handler_robot_.set_heading_angle(ha);
  }
  double get_speed(void) const override {
    return motion_handler_robot_.get_speed();
  }
  void set_speed(double sp) override { motion_handler_robot_.set_speed(sp); }

  std::string get_name(void) const override { return "Robot"; }

  Position get_initial_position() {return initial_position_;}

  double get_proximity_range() const {
    return sensor_proximity_robot_.get_range();
  }

  double get_proximity_fov() const {
    return sensor_proximity_robot_.get_field_of_view();
  }

  SensorTouch* get_sensor_t() { return &sensor_touch_robot_; }
  SensorProximity* get_sensor_p() { return &sensor_proximity_robot_; }

 private:
  SensorTouch sensor_touch_robot_;
  SensorProximity sensor_proximity_robot_;
  SensorDistress sensor_distress_robot_;
  SensorEntityType sensor_entity_type_robot_;
  MotionHandlerRobot motion_handler_robot_;
  Position initial_position_;
};

NAMESPACE_END(csci3081);

#endif /* SRC_ROBOT_H_ */
