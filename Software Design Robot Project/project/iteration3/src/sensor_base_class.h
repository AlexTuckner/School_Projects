/**
 * @file Sensor_base_class.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */


#ifndef SRC_SENSOR_BASE_CLASS_H_
#define SRC_SENSOR_BASE_CLASS_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/common.h"
#include "src/event_entity_base_class.h"
#include "src/entity_type.h"
#include "src/event_proximity.h"
#include "src/event_type_emit.h"
#include "src/event_distress_call.h"
#include "src/event_collision.h"


/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * \class Sensor
 * @brief The base Sensor class from which all sensors should derive from.
 */
class Sensor {
 public:
  Sensor(enum entity_type t, int activated) :
  type(t),
  is_activated(activated) {}

  /**
   * \fn void Accept(const Event______ * const e)
   * @brief Accept each type of entity event and respond accordingly
   *
   */
  virtual void Accept(const EventCollision * const e) = 0;
  virtual void Accept(const EventProximity * const e) = 0;
  virtual void Accept(const EventDistressCall * const e) = 0;
  virtual void Accept(const EventTypeEmit * const e) = 0;
  virtual void Output() = 0;

  enum entity_type get_entity_type() { return type; }
  void set_entity_type(enum entity_type t) { type = t; }

  int get_is_activated() { return is_activated; }
  void set_is_activated(int a) { is_activated = a; }

 private:
  enum entity_type type;
  int is_activated;
};

NAMESPACE_END(csci3081);

#endif /* SRC_SENSOR_BASE_CLASS_H_ */
