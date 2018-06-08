/**
 * @file player_params.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_player_params_H_
#define SRC_player_params_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/arena_mobile_entity_params.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Structure Definitions
 ******************************************************************************/
 /**
  * \subsection struct player_params : public arena_mobile_entity_params
  * @brief Inherits from mobile_entity_params to set various
  * properties of the player.
  **/
struct player_params : public arena_mobile_entity_params {
  player_params(void) :
      arena_mobile_entity_params(),
      battery_max_charge(),
      angle_delta() {}

  double battery_max_charge;
  uint angle_delta;
};

NAMESPACE_END(csci3081);

#endif /* SRC_player_params_H_ */
