/**
 * @file event_collision.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_EVENT_TYPE_EMIT_H_
#define SRC_EVENT_TYPE_EMIT_H_

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
 * \class EventTypeEmit : public EventEntityBaseClass
 * @brief An event class, which is created to emit the type of objects
 * that are nearby an object. Different objects react differently when
 * different entities are nearby, such as a Robot towards the home base. 
 */
class EventTypeEmit : public EventEntityBaseClass {
 public:
  EventTypeEmit(enum entity_type entity, Position position_of_event) :
  EventEntityBaseClass(entity, position_of_event) {}
};

NAMESPACE_END(csci3081);

#endif /* SRC_EVENT_TYPE_EMIT_H_ */
