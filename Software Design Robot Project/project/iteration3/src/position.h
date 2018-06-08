/**
 * @file position.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_POSITION_H_
#define SRC_POSITION_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/common.h"
#include "src/color.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * \class Position
 * @brief A simple representation of a position of an entity within the arena.
 */
class Position {
 public:
  Position(void) : x_(0), y_(0) {}
  Position(int in_x, int in_y) : x_(in_x), y_(in_y) { }

  int get_x(void) const { return x_; }
  int get_y(void) const { return y_; }
  void set_x(double x) { x_ = x; }
  void set_y(double y) { y_ = y; }

  Position& operator=(const Position& other) {
    this->x_ = other.x_;
    this->y_ = other.y_;
    return *this;
  }

 private:
  double x_;
  double y_;
};
NAMESPACE_BEGIN(csci3081);

NAMESPACE_END(csci3081);

#endif /* SRC_POSITION_H_ */
