/**
 * @file sensor_touch.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_SENSOR_PROXIMITY_H_
#define SRC_SENSOR_PROXIMITY_H_

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
class SensorProximity: public Sensor {
 public:
  SensorProximity(enum entity_type t, int activated, double r, double fov) :
    Sensor(t, activated),
    range(r),
    field_of_view(fov), left_(false), right_(false) {}

    /**
     * \fn void Accept(const Event______ * const e)
     * @brief Accept each type of entity event and respond accordingly
     *
     */
  void Accept(const EventCollision * const e) {}
  void Accept(const EventDistressCall * const e) {}
  void Accept(const EventTypeEmit * const e) {}
  void Accept(const EventProximity * const e);
  void Output() {}


  /**
   * \fn void Reset(void)
   * @brief Reset the proximity sensor to its newly constructed state.
   */
  void Reset(void);


  double get_field_of_view() const {return field_of_view;}
  void set_field_of_view(double fov) { field_of_view = fov;}
  double get_range() const {return range;}
  void set_range(double r) {range = r;}
  bool get_left() { return left_;}
  void set_left(bool l) { left_ = l;}
  bool get_right() { return right_;}
  void set_right(bool r) { right_ = r;}

 private:
  double range;
  double field_of_view;
  bool left_;
  bool right_;
};

NAMESPACE_END(csci3081);

#endif /* SRC_SENSOR_TOUCH_H_ */
