/**
 * @file event_keypress.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/event_keypress.h"
#include "src/graphics_arena_viewer.h"
#include "src/robot.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
enum event_commands EventKeypress::keypress_to_cmd() const {
  /*
   * These values are likely not universal across all OS's.
   * Write a wrapper for the various OS or see if nanogui has that
   * functionality.
   */
  switch (key_) {
    case GLFW_KEY_LEFT:
      return COM_TURN_LEFT;
      break;
    case GLFW_KEY_RIGHT:
      return COM_TURN_RIGHT;
      break;
    case GLFW_KEY_UP:
      return COM_SPEED_UP;
      break;
    case GLFW_KEY_DOWN:
      return COM_SLOW_DOWN;
      break;
    default:
      printf("Unknown keypress: %d\n", key_);
      assert(0);
  } /* switch() */
} /* keypress_to_cmd() */

NAMESPACE_END(csci3081);
