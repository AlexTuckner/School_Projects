/**
 * @file actuator_handler.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_MOTION_HANDLER_BASE_H_
#define SRC_MOTION_HANDLER_BASE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/event_commands.h"
#include "src/arena_mobile_entity.h"
#include "src/sensor_touch.h"
#include "src/arena_entity_params.h"
#include "src/common.h"
/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Classes
 ******************************************************************************/
/**
 * \class MotionHandlerBase
 * @brief The base class for all motion handlers.
 * As the name suggests, this is intended to handle the motion of each mobile
 * mobile object in the arena, and each will have its own class derived from
 * this one as they will all beave slightly differently.
 *
 * For this iteration, both wheels are always going at maximum speed, and
 * cannot be controlled independently.
 */
class MotionHandler {
 public:
  MotionHandler(double heading, double speed);
  /**
   * \fn void Reset(void)
   * @brief Reset the actuators to their newly constructed/un-commanded state.
   */
  void Reset(void);

  /**
  * \fn void Stop(void);
  * @brief Stop the entity from moving
  * For example, if the game ends
  */
  void Stop(void) { speed_ = 0; }

  double get_speed(void) const { return speed_; }
  void set_speed(double sp) { speed_ = sp; }

  double get_heading_angle(void) const { return heading_angle_;}
  void set_heading_angle(double ha) { heading_angle_ = ha; }

  double get_max_speed(void) const { return max_speed_; }
  void set_max_speed(double ms) { max_speed_ = ms; }

  double get_initial_heading_angle() {return initial_heading_angle_;}
  double get_initial_speed() {return initial_speed_;}

 private:
  double heading_angle_;
  double speed_;
  double max_speed_;
  double initial_heading_angle_;
  double initial_speed_;
};

NAMESPACE_END(csci3081);

#endif /* SRC_MOTION_HANDLER_BASE_H_ */
