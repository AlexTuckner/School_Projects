/**
 * @file event_collision.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_EVENT_COLLISION_H_
#define SRC_EVENT_COLLISION_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdlib.h>
#include "src/event_base_class.h"
#include "src/position.h"
#include "src/event_entity_base_class.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * \class EventCollision : public EventEntityBaseClass
 * @brief A collision event class, which is created after a
 * \ref MobileArenaEntity gets within a specified distance of another entity in
 * the arena, OR when an entity that was previously within the collision delta
 * of other entity outside of that threshold.
 */
class EventCollision : public EventEntityBaseClass {
 public:
  EventCollision(enum entity_type entity,
            Position position_of_event, double aoc) :
  EventEntityBaseClass(entity, position_of_event),
  collided_(false),
  angle_of_contact_(aoc) {}

  /**
   * \fn bool collided(void) const / void collided(bool c)
   * @brief If \c TRUE, then this instance represents an active collision
   * event. If \c FALSE, then it represents a previous collision event that has
   * been resolved.
   */
  bool get_collided() const {return collided_;}
  void set_collided(bool c) {collided_ = c;}

  /**
   * \fn Position point_of_contact(void) / void point_of_contact(Position p)
   * @brief The point in the arena at which the entities have collided/touched.
  //  */
  // Position get_point_of_contact(void) const { return point_of_contact_; }
  // void set_point_of_contact(Position p) { point_of_contact_ = p; }

  /**
   * \fn double angle_of_contact(void) const / void angle_of_contact(double aoc)
   * @brief The angle, in degrees, as specified on the unit circle, that the
   * collision occurred at. Needed to calculate the outgoing/bounceback angle.
   */
  double get_angle_of_contact(void) const { return angle_of_contact_; }
  void set_angle_of_contact(double aoc) { angle_of_contact_ = aoc; }

 private:
  double angle_of_contact_;
  bool collided_;
};

NAMESPACE_END(csci3081);

#endif /* SRC_EVENT_COLLISION_H_ */
