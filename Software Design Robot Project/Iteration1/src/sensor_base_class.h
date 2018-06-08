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
#include "src/event_collision.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * \class SensorBaseClass
 * @brief The base Sensor class from which all sensors should derive from.
 */
class SensorBaseClass {
 public:
  SensorBaseClass(void) {}
};

NAMESPACE_END(csci3081);

#endif /* SRC_EVENT_BASE_CLASS_H_ */
