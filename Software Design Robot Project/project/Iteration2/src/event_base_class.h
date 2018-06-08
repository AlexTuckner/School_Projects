/**
 * @file event_base_class.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_EVENT_BASE_CLASS_H2_
#define SRC_EVENT_BASE_CLASS_H2_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/common.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * \class EventBaseClass
 * @brief The base event class from which all events derive from.
 */
class EventBaseClass {
 public:
  EventBaseClass() = default;
  virtual ~EventBaseClass() = default;

  /**
   * \fn virtual void EmitMessage(void) = 0;
   * @brief Each event, upon its firing, should emit a message to the user on
   * stdout saying what happened, in order to aid debugging.
   *
   */
  virtual void EmitMessage() const = 0;
};

NAMESPACE_END(csci3081);

#endif /* SRC_EVENT_BASE_CLASS_H_ */
