/**
 * @file event_collision.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_EVENT_DISTRESS_CALL_H_
#define SRC_EVENT_DISTRESS_CALL_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdlib.h>
#include "src/event_entity_base_class.h"
#include "src/position.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * \class EventDistressCall : public EventBaseClass
 * @brief A distress event class, which is created after a
 * player collides with the robot.  This will remove the proximity sensors
 * of a SuperBot so that it can collide, and freeze the player.
 */
class EventDistressCall : public EventEntityBaseClass {
 public:
  EventDistressCall(enum entity_type entity, Position position_of_event) :
    EventEntityBaseClass(entity, position_of_event), frozen(false) {}

 /*!
  * \fn get_is_frozen / set_is_frozen
  * This is a function used to determine if the object should be frozen or not
  */
  bool get_is_frozen() const {return frozen;}
  void set_is_frozen(bool f) {frozen = f;}

 private:
  bool frozen;
};

NAMESPACE_END(csci3081);

#endif /* SRC_EVENT_DISTRESS_CALL_H_ */
