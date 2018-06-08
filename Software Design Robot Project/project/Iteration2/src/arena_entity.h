/**
 * @file arena_entity.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_ARENA_ENTITY_H_
#define SRC_ARENA_ENTITY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <nanogui/nanogui.h>
#include <string>
#include "src/common.h"
#include "src/position.h"
#include "src/color.h"
#include "src/entity_type.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * \class ArenaEntity
 * @brief A base class representing an entity within the arena. All entities
 * within the arena know how to :
 *
 * 1. Update themselves each timestep (i.e. in accordance with current velocity
 *    and position).
 *
 * 2. Reset themselves to a newly constructed state. This is so the user can
 *    click the reset button after completing a game and have things work as
 *    expected.
 *
 * Please note that here use the upper-left coordinate, which means that the
 * origin point (0.0,0.0) is at the upper left.
 *
 * Also, all arena entities are circular.
 */
class ArenaEntity {
 public:
  ArenaEntity(double radius, enum entity_type e, const Position& pos,
              const csci3081::Color& color) :
      radius_(radius), pos_(pos), color_(color), entity_type_(e) {}
  virtual ~ArenaEntity(void) {}

  /*!
   * \fn virtual void TimestepUpdate(__unused uint dt)
   * @brief Perform whatever updates are needed for a particular entity after 1
   * timestep (updating position, changing color, etc.).
   */
  virtual void TimestepUpdate(__unused uint dt) {}

  /*!
   * \fn Reset virtual void Reset(void)
   * @brief Reset the entity to its newly constructed state.
   */
  virtual void Reset(void) {}

  /*!
   * \fn Getters and Setters
   * @brief Get the name of an entity for visualization purposes, to aid in
   * debugging.
   */
  virtual std::string get_name(void) const = 0;

  void set_pos(const Position& pos) { pos_ = pos; }
  const Position& get_pos(void) const { return pos_; }
  const csci3081::Color& get_color(void) const { return color_; }
  void set_color(const csci3081::Color& color) { color_ = color; }
  double get_radius(void) const { return radius_; }
  void set_entity_type(enum entity_type e) { entity_type_ = e; }
  enum entity_type get_entity_type() const { return entity_type_; }

 private:
  double radius_;
  Position pos_;
  csci3081::Color color_;
  enum entity_type entity_type_;
};

NAMESPACE_END(csci3081);

#endif /* SRC_ARENA_ENTITY_H_ */
