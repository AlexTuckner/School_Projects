/**
 * @file actuator_handler.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_MOTION_HANDLER_ROBOT_H_
#define SRC_MOTION_HANDLER_ROBOT_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/event_commands.h"
#include "src/motion_handler_base.h"
#include "src/sensor_proximity.h"
/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Classes
 ******************************************************************************/
/**
 * \class MotionHandlerRobot: public MotionHandler
 * @brief The handler for the robots that are in the arena.  They use an event
 * collision and event proximity to change direction according to the sensors.
 */
class MotionHandlerRobot: public MotionHandler {
 public:
  MotionHandlerRobot(double heading, double speed);

  /**
  * \fn void AcceptCollision(SensorTouch st)
  * @brief Change the speed and direction according to the sensor readings.
  *
  * @param touch sensor that can be activated and contains point-of-contact.
  *
  */
  void AcceptCollision(SensorTouch st);

  /**
  * \fn void AcceptProximity(SensorTouch sp)
  * @brief Change the speed and direction according to the sensor readings.
  *   If an object is seen on the robot's left or right, then the robot should
  *   try to avoid it.
  * @param touch sensor that can be activated and contains point-of-contact.
  *
  */
  void AcceptProximity(SensorProximity sp);
};

NAMESPACE_END(csci3081);

#endif /* SRC_MOTION_HANDLER_ROBOT_H_ */
