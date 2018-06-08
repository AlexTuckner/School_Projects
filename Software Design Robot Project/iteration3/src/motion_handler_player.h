/**
 * @file actuator_handler.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_MOTION_HANDLER_PLAYER_H_
#define SRC_MOTION_HANDLER_PLAYER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/event_commands.h"
#include "src/player_params.h"
#include "src/motion_handler_base.h"
/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Classes
 ******************************************************************************/
/**
 * \class MotionHandlerPlayer
 * Manages the modification to the velocity based on user input and
 * collisions. \ref PlayerMotionBehavior translates velocity and position to a
 * new position. 
 */
class MotionHandlerPlayer: public MotionHandler {
 public:
  MotionHandlerPlayer(double heading, double speed);


  /**
   * \fn void AcceptCommand(enum event_commands cmd)
   * @brief Command from user keypress via the viewer.
   *
   * @param cmd The command.
   */
  void AcceptCommand(enum event_commands cmd);

  /**
  * \fn void AcceptCollision(SensorTouch st)
  * @brief Change the speed and direction according to the sensor readings.
  *
  * @param touch sensor that can be activated and contains point-of-contact.
  *
  */
  void AcceptCollision(SensorTouch st);

  /**
  * \fn void UpdateVelocity(SensorTouch st)
  * @brief Change the speed and direction according to the sensor readings.
  *
  * @param touch sensor that can be activated and contains point-of-contact.
  *
  */
  void UpdateVelocity(SensorTouch st);
};

NAMESPACE_END(csci3081);

#endif /* SRC_MOTION_HANDLER_PLAYER_H_ */
