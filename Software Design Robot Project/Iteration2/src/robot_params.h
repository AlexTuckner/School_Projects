/**
 * @file home_base_params.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_ROBOT_PARAMS_H_
#define SRC_ROBOT_PARAMS_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/arena_entity_params.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Structure Definitions
 ******************************************************************************/
struct robot_params : public arena_entity_params {
  robot_params(void) : arena_entity_params(),
                              collision_delta() {}

/**
* Minimum distance between entities that qualifies as a collision.
*/
double collision_delta;
int ent_Num;
};

NAMESPACE_END(csci3081);

#endif /* SRC_ROBOT_PARAMS_H_ */
