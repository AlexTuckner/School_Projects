/**
 * @file actuator_handler.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_MOTION_HANDLER_HOME_BASE_H_
#define SRC_MOTION_HANDLER_HOME_BASE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/event_commands.h"
#include "src/player_params.h"
#include "src/arena_mobile_entity.h"
#include "src/position.h"
#include "src/common.h"
#include "src/motion_handler_base.h"
/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Classes
 ******************************************************************************/
/**
 * \class MotionHandlerHomeBase
 * @brief The handler for the Home Base, pretty simple as there is no special
 * implentation except that it randomly changes direction, which is currently
 * implented in the homebase class.  I will fill this in the bug report and
 * will move that here in the future
 */
class MotionHandlerHomeBase: public MotionHandler {
 public:
  MotionHandlerHomeBase(double heading, double speed);

  /**
  * \fn void AcceptCollision(SensorTouch st)
  * @brief Change the speed and direction according to the sensor readings.
  *
  * @param touch sensor that can be activated and contains point-of-contact.
  *
  */
  void AcceptCollision(SensorTouch st);
};

NAMESPACE_END(csci3081);

#endif /* SRC_MOTION_HANDLER_HOME_BASE_H_ */
