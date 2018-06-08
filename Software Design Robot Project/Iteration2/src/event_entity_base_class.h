/**
 * @file event_collision.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_EVENT_ENTITY_BASE_CLASS_H_
#define SRC_EVENT_ENTITY_BASE_CLASS_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include "src/event_base_class.h"
#include "src/position.h"
#include "src/entity_type.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * \class EventEntityBaseClass : public EventBaseClass
 * @brief A base class for all the entity events.
 * this class is useful because many of these events have the same attributes
 * such as a Position and the entities involved
 */
class EventEntityBaseClass : public EventBaseClass {
 public:
  EventEntityBaseClass(enum entity_type entity, Position position_of_event) :
  entity_involved(entity),
  event_location(position_of_event) {}

  /**
   * \fn virtual void EmitMessage(void);
   * @brief Each event, upon its firing, should emit a message to the user on
   * stdout saying what happened, in order to aid debugging.
   *
   */
  void EmitMessage(void) const override { printf("Event Base Class\n"); }


  enum entity_type get_entity_involved() const {return entity_involved;}
  void set_entity_involved(enum entity_type e) {entity_involved = e;}

  Position get_event_location() const {return event_location;}
  void set_event_location(Position p) { event_location = p;}

 private:
  enum entity_type entity_involved;
  Position event_location;
};

NAMESPACE_END(csci3081);

#endif /* SRC_EVENT_ENTITY_BASE_CLASS_H_ */
