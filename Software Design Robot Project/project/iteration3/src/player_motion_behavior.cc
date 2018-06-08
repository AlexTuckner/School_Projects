/**
 * @file player_motion_behavior.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/player_motion_behavior.h"
#include "src/position.h"
#include "src/arena_mobile_entity.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void PlayerMotionBehavior::UpdatePosition(ArenaMobileEntity * const ent,
                                         unsigned int dt) {
  // Save position for debugging purposes
  Position new_pos = ent->get_pos();
  Position old_pos = ent->get_pos();

  // Movement is always along the heading_angle (i.e. the hypotenuse)
  new_pos.set_x(new_pos.get_x() + cos(ent->get_heading_angle()*M_PI/180.0)*
            ent->get_speed()*dt);
  new_pos.set_y(new_pos.get_y() + sin(ent->get_heading_angle()*M_PI/180.0)*
            ent->get_speed()*dt);
  ent->set_pos(new_pos);
} /* update_position() */

NAMESPACE_END(csci3081);
