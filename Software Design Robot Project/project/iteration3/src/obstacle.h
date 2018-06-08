/**
 * @file obstacle.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_OBSTACLE_H_
#define SRC_OBSTACLE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "src/arena_immobile_entity.h"
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
 * \class Obstacle: public ArenaImmobileEntity
 * @brief This class contains the immobile obstacles placed throughout the
 * game.  They are made to restrict the user from getting to the goal.
 */

class Obstacle: public ArenaImmobileEntity {
 public:
  Obstacle(double radius, enum entity_type et, const Position& pos,
     const csci3081::Color& color);

  std::string get_name(void) const override {
    return "Obstacle" + std::to_string(id_);
  }

  void reset_next_id() { next_id_ = 0;}

 private:
  static uint next_id_;
  int id_;
};

NAMESPACE_END(csci3081);

#endif /* SRC_OBSTACLE_H_ */
