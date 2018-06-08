/**
 * @file event_commands.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 *
 */

#ifndef SRC_ENTITY_TYPE_H_
#define SRC_ENTITY_TYPE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/common.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Type Definitions
 ******************************************************************************/
/**
 * \subsection entity_type
 * @brief The supported types of entities that can be found in the arena
 */
enum entity_type {
  kPlayer,
  kSuperBot,
  kRobot,
  kHomeBase,
  kObstacle,
  kRechargeStation,
  kWall
};

NAMESPACE_END(csci3081);

#endif /* SRC_ENTITY_TYPE_H_ */
