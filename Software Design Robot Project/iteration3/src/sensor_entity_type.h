/**
 * @file sensor_touch.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_SENSOR_ENTITY_TYPE_H_
#define SRC_SENSOR_ENTITY_TYPE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>
#include <utility>

#include "src/common.h"
#include "src/sensor_base_class.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Classes
 ******************************************************************************/
/**
 * \class SensorDistress
 */
class SensorEntityType: public Sensor {
 public:
  SensorEntityType(enum entity_type t, int activated, double r) :
    Sensor(t, activated),
    range(r) {}

  /**
   * \fn void Accept(const Event______ * const e)
   * @brief Accept each type of entity event and respond accordingly
   *
   */
  void Accept(const EventCollision * const e) {}
  void Accept(const EventDistressCall * const e) {}
  void Accept(const EventTypeEmit * const e) {}
  void Accept(const EventProximity * const e) {}
  void Output() {}

  /**
   * \fn void Reset(void)
   * @brief Reset the proximity sensor to its newly constructed state.
   */
  void Reset(void);

  double get_range() {return range;}
  void set_range(double r) {range = r;}


 private:
  double range;
};

NAMESPACE_END(csci3081);

#endif /* SRC_SENSOR_TOUCH_H_ */
