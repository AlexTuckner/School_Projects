/**
 * @file sensor_touch.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_SENSOR_TOUCH_H_
#define SRC_SENSOR_TOUCH_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>
#include <utility>

#include "src/common.h"
#include "src/event_collision.h"
#include "src/sensor_base_class.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Classes
 ******************************************************************************/
class ArenaEntity;

/**
 * \class SensorTouch: public SensorBaseClass
 * @brief A representation of a touch sensor.
 *
 * Touch or "bump" sensors are "active" when pressed. For our purposes, imagine
 * a series of bump sensors around the perimeter of the player. A collision will
 * activate the sensor at a particular point of contact, which translates to an
 * angle of contact.
 */
class SensorTouch: public Sensor {
 public:
  SensorTouch(enum entity_type t, int activated, Position poc, double aoc) :
    Sensor(t, activated),
    point_of_contact_(poc),
    angle_of_contact_(aoc) {}

  /**
   * \fn void Accept(const Event______ * const e)
   * @brief Accept each type of entity event and respond accordingly
   *
   */
  void Accept(const EventCollision * const e);
  void Accept(const EventDistressCall * const e) {}
  void Accept(const EventTypeEmit * const e) {}
  void Accept(const EventProximity * const e) {}
  void Output() {}

  /**
   * \fn void Reset(void)
   * @brief Reset the proximity sensor to its newly constructed state.
   */
  void Reset(void);

  Position get_point_of_contact() { return point_of_contact_; }
  void set_point_of_contact(Position p) {
    point_of_contact_ = p;
  }

  double get_angle_of_contact(void) { return angle_of_contact_; }
  void set_angle_of_contact(double aoc) { angle_of_contact_ = aoc; }

 private:
  Position point_of_contact_;
  double angle_of_contact_;
};

NAMESPACE_END(csci3081);

#endif /* SRC_SENSOR_TOUCH_H_ */
