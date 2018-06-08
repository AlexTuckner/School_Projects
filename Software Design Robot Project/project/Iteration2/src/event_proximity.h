/**
 * @file event_collision.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_EVENT_PROXIMITY_H_
#define SRC_EVENT_PROXIMITY_H_

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
 * \class EventProximity : public EventEntityBaseClass
 * @brief A Proximity event class, which is created after another
 * entity gets within a specified distance of the robot.
 * This event signals for the robot to turn out of the way of incoming objects
 */
class EventProximity : public EventEntityBaseClass {
 public:
  EventProximity(enum entity_type entity, Position position_of_event) :
  EventEntityBaseClass(entity, position_of_event),
  in_range_(false), event_left_(false), event_right_(false) {}


  bool get_in_range() const {return in_range_;}
  void set_in_range(bool b) {in_range_ = b;}
  bool get_event_left() const {return event_left_;}
  void set_event_left(bool l) { event_left_ = l;}
  bool get_event_right() const {return event_right_;}
  void set_event_right(bool r) { event_right_ = r;}

 private:
  bool in_range_;
  bool event_left_;
  bool event_right_;
};

NAMESPACE_END(csci3081);

#endif /* SRC_EVENT_PROXIMITY_H_ */
