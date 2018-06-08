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

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * \class HomeBase : public ArenaMobileEntity
 * @brief The goal the robot is trying to drive to within the arena.
 *
 * This class is now a mobile entity and has been made to move randomly
 */
class HomeBase : public ArenaMobileEntity {
 public:
  explicit HomeBase(const struct home_base_params* const params);
  void TimestepUpdate(unsigned int dt) override;

  double heading_angle(void) const override { return heading_angle_;}
  void heading_angle(double ha) override { heading_angle_ = ha; }
  double get_speed(void) const override { return speed; }
  void set_speed(double sp) override { speed = sp; }
  void Accept(const EventCollision * const e) override;
  int get_ent_Num() const {return ent_Num;}
  void set_ent_Num(int n) {ent_Num = n;}
  void Reset(void) override;
  std::string get_name(void) const override { return "Home Base"; }
  void Stop(void) { speed = 0; }

 private:
  double heading_angle_;
  double speed;
  SensorTouch sensor_touch_home;
  int ent_Num;
  Position initial_position;
  double initial_heading_angle;
  double heading;
  int randangle;
  int randvalue;
};

NAMESPACE_END(csci3081);

#endif /* SRC_HOME_BASE_H_ */
