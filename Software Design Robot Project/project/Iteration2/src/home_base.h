/**
 * @file home_base.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_HOME_BASE_H_
#define SRC_HOME_BASE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "src/home_base_params.h"
#include "src/arena_mobile_entity.h"
#include "src/sensor_touch.h"
#include "src/event_collision.h"
#include "src/event_command.h"
#include "src/motion_handler_home_base.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * \class HomeBase : public ArenaMobileEntity
 * @brief The homebase in which robots collide into to become superbots
 *
 * This class is now a mobile entity and has been made to move randomly
 */
class HomeBase : public ArenaMobileEntity {
 public:
  explicit HomeBase(const struct home_base_params* const params);
  void TimestepUpdate(unsigned int dt) override;
  void Accept(const EventCollision * const e) override;
  void Reset(void) override;
  void Stop(void);

  double get_heading_angle(void) const override {
    return motion_handler_home_.get_heading_angle();
  }
  void set_heading_angle(double ha) override {
    motion_handler_home_.set_heading_angle(ha);
  }
  double get_speed(void) const override {
    return motion_handler_home_.get_speed();
  }
  void set_speed(double sp) override { motion_handler_home_.set_speed(sp); }

  std::string get_name(void) const override { return "Home Base"; }

  Position get_initial_position() {return initial_position_;}

  SensorTouch* get_sensor_t() { return &sensor_touch_home; }

 private:
  SensorTouch sensor_touch_home;
  MotionHandlerHomeBase motion_handler_home_;
  Position initial_position_;
  int randangle;
  int randvalue;
};

NAMESPACE_END(csci3081);

#endif /* SRC_HOME_BASE_H_ */
