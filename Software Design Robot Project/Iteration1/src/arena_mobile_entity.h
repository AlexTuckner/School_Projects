/**
 * @file mobile_arena_entity.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_ARENA_MOBILE_ENTITY_H_
#define SRC_ARENA_MOBILE_ENTITY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <algorithm>
#include "src/arena_entity.h"
#include "src/event_base_class.h"
#include "src/event_recharge.h"
#include "src/event_collision.h"
#include "src/color.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/*!
 * \class ArenaMobileEntity : public ArenaEntity
 * @brief A mobile entity in the arena, capable of updating its own position
 * and/or velocity when asked by the simulation.
 *
 * All mobile entities must have a heading angle so that their orientation can
 * be properly drawn by the viwer.
 */
class ArenaMobileEntity : public ArenaEntity {
 public:
  ArenaMobileEntity(double radius, double collision_delta,
                    const Position& pos, const csci3081::Color& color) :
      ArenaEntity(radius, pos, color),
      collision_delta_(collision_delta) {}

  /*!
   * \fn virtual double heading_angle(void) const = 0;
   * @brief Get the current heading angle for the entity.
   */
  virtual double heading_angle(void) const = 0;

  /*!
   * \fn virtual void heading_angle(double heading_angle) = 0;
   * @brief Set the new heading angle for the entity.
   *
   * This should only be called by a dedicated motion handler class, and only
   * from within \ref Timestepupdate().
   */
  virtual void heading_angle(double heading_angle) = 0;

  /*!
   * \fn virtual double get_speed(void) const = 0;
   * @brief Get the current speed of an arena entity.
   */
  virtual double get_speed(void) const = 0;

  /*!
   * \fn set_speed()
   * @brief Set the new speed of an entity.
   *
   * This should only be called by a dedicated motion handler class, and only
   * from within \ref Timestepupdate().
   */
  virtual void set_speed(double sp) = 0;

  /*!
   * \fn virtual void Accept(const EventCollision * const e) = 0;
   * @brief Accept a visit from a collision event, updating state appropriately.
   */
  virtual void Accept(const EventCollision * const e) = 0;

  /*!
   * \fn void Accept(const EventRecharge * const e);
   * @brief Accept a visit from a recharge event, updating state appropriately.
   *
   * Note that this is robot-specific, and should be removed as a pure virtual
   * function once the \ref HomeBase class is made mobile.
   */
  void Accept(const EventRecharge * const e);

  /*!
   * \fn void TimestepUpdate(uint dt) override;
   * @brief Update an entity's position and velocity after the specified # of
   * timesteps has elapsed.
   *
   * @param dt The # of timesteps that has elapsed since the last time
   * position/velocity were updated.
   */
  void TimestepUpdate(uint dt) override;

  /*!
   * \fn double collision_delta(void) const a
   * @brief Get the minimum distance between two arena entities that will be
   * considered a collision.
   *
   */
  double collision_delta(void) const { return collision_delta_; }

  Position get_Last_Position() {return last_Position;}
  void set_Last_Position(Position p) { last_Position = p;}
  Position get_Second_Last_Position() {return second_last_Position;}
  void set_Second_Last_Position(Position p) { second_last_Position = p;}

  /*!
   * \fn get_ent_Num()/set_ent_Num()
   * @brief Created an entity num for the mobile entities to distinguish
   * then from one another.
   */
  virtual int get_ent_Num() const {return ent_Num;}
  virtual void set_ent_Num(int n) {ent_Num = n;}

  Position get_initial_Pos() {return initial_pos;}
  void set_initial_Pos(Position p) { initial_pos = p;}

 private:
  double collision_delta_;
  int ent_Num = 0;
  Position last_Position;
  Position second_last_Position;
  Position initial_pos;
};

NAMESPACE_END(csci3081);

#endif /* SRC_ARENA_MOBILE_ENTITY_H_ */
