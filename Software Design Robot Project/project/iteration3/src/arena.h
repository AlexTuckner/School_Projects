/**
 * @file player_arena.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_ARENA_H_
#define SRC_ARENA_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <cmath>
#include <iostream>
#include <vector>
#include "src/event_keypress.h"
#include "src/event_collision.h"
#include "src/sensor_touch.h"
#include "src/robot.h"
#include "src/superbot.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
struct arena_params;

/**
 * \class Arena
 * @brief The main class for the simulation of a 2D world with many players running
 * around.
 *
 * \ref GraphicsArenaViewer or Tests call \ref AdvanceTime to control the
 * simulation and use the get*() functions to read out the current state of the
 * simulation (i.e., the current positions and orientations of players and
 * obstacles).
 */
class Arena {
 public:
  explicit Arena(const struct arena_params * const params);
  ~Arena(void);

  /**
   * \fn void AdvanceTime(double dt)
   * @brief Advance the simulation by the specified # of steps.
   *
   * @param[in] dt The # of steps to increment by.
   */
  void AdvanceTime(double dt);

  /**
  * \fn void Accept(const EventKeypress * const e)
  * @brief Handle the key press passed along by the viewer.
  *
  * @param[in] an event holding the key press.
  *
  */
  void Accept(const EventKeypress * const e);

  /**
   * \fn void Reset(void)
   * @brief Reset all entities in the arena, effectively restarting the game.
   */
  void Reset(void);

  /*
   * \fn unsigned int get_n_players(void)
   * @brief Get the # of players in the arena.
   */
  unsigned int get_n_players(void) { return n_players_; }

  /*
   * \fn unsigned int get_n_obstacles(void)
   * @brief Get # of obstacles in the arena.
   */
  unsigned int get_n_obstacles(void) { return n_obstacles_; }

  /**
   * \fn std::vector<class Obstacle*> obstacles(void)
   * @brief Get a list of all obstacles (i.e. non-mobile entities in the arena).
   */
  std::vector<class Obstacle*> obstacles(void);


  double get_battery_level() {return batterylevel;}
  void set_battery_level(double b) {batterylevel = b;}

  void set_wins(double w) {wins = w;}
  double get_wins() {return wins;}

  void set_losses(double l) {losses = l;}
  double get_losses() {return losses;}

  void set_win(bool w) {win = w;}
  bool get_win() {return win;}

  void set_loss(bool l) {loss = l;}
  bool get_loss() {return loss;}

  /**
   * \fn std::vector<class ArenaMobileEntity*> mobile_entities(void)
   * @brief Get the list of all mobile entities in the arena.
   */
  std::vector<class ArenaMobileEntity*> mobile_entities(void)
    { return mobile_entities_; }

    /*!
     * \fn class RechargeStation* recharge_station(void) const
     * @brief Returns a RechargeStation object pointer
     */
  class RechargeStation* recharge_station(void) const {
    return recharge_station_;
  }

  /*!
   * \fn class Player* player(void) const
   * @brief Returns a Player object pointer
   */
  class Player* player(void) const { return player_; }

  /*!
   * \fn class HomeBase* home_base(void) const
   * @brief Returns a HomeBase object pointer
   */
  class HomeBase* home_base(void) const { return home_base_; }

  /*!
   * \fn std::vector<class Robot*> robots(void);
   * @brief Returns a vector of Robot pointers
   */
  std::vector<class Robot*> robots(void);

  /*!
   * \fn std::vector<class SuperBot*> superbots(void);
   * @brief Returns a vector of superbot pointers
   */
  std::vector<class SuperBot*> superbots(void);

 private:
  /**
   * \fn bool any_entities_overlap(void);
   * @brief Determine if any entities in the arena are overlapping.
   *
   * @return TRUE if any entities overlap, FALSE if no entities overlap.
   */
  bool any_entities_overlap(void);

  /**
   * \fn void CheckForEntityCollision(const class ArenaMobileEntity* const ent1,
                                  const class ArenaEntity* const ent2,
                                  EventCollision * const ec,
                                  double collision_delta)
   * @brief Determine if two entities have collided in the arena. Collision is
   * defined as the difference between the extents of the two entities being less
   * than a run-time parameter.
   *
   * @param ent1 Entity #1.
   * @param ent2 Entity #2.
   * @param pointer to a collision event
   *
   * Collision Event is populated appropriately.
   */
  void CheckForEntityCollision(const class ArenaMobileEntity* const ent1,
                               const class ArenaEntity* const ent2,
                               EventCollision * const ec,
                               double collision_delta);

  /**
   * \fn CheckForEntityOutOfBounds(const class ArenaMobileEntity* const ent,
                                  EventCollision * const ec)
   * @brief Determine if a particular entity is gone out of the boundaries of
   * the simulation.
   *
   * @param ent The entity to check.
   * @param pointer to a collision event.
   *
   * Collision event is populated appropriately.
   */
  void CheckForEntityOutOfBounds(const class ArenaMobileEntity* const ent,
                                 EventCollision * const ec);

   /**
    * \fn void CheckForObjectInProximity(const class Robot* const ent1,
                                    const class ArenaEntity* const ent2,
                                    EventProximity * const ep);
    * @brief Determine if a particular entity is in one of the robot's
    * proximity sensors
    *
    * @param ent1 The robot with the sensor.
    * @param ent2 The entity being scanned with the sensor.
    * @param pointer to a proximity event.
    *
    * Collision event is populated appropriately.
    */
  void CheckForObjectInProximity(const class Robot* const ent1,
                                const class ArenaEntity* const ent2,
                                EventProximity * const ep);

                                /**
     * \fn void CheckForObjectInProximity(const class Robot* const ent1,
                                     const class ArenaEntity* const ent2,
                                     EventProximity * const ep);
     * @brief Determine if a particular entity is in one of the robot's
     * proximity sensors
     *
     * @param ent1 The robot with the sensor.
     * @param ent2 The entity being scanned with the sensor.
     * @param pointer to a proximity event.
     *
     * Collision event is populated appropriately.
     */
  void CheckForObjectInProximity(const class SuperBot* const ent1,
                                 const class ArenaEntity* const ent2,
                                 EventProximity * const ep);
  /**
   * \fn ouble Positive(int angle);
   * @brief A quick function that will always make an angle positive
   */
  double Positive(int angle);

  /**
   * \fn void UpdateEntitiesTimestep(void)
   * @brief Update all entities for a single timestep
   */
  void UpdateEntitiesTimestep(void);

  // Under certain circumstance, the compiler requires that the copy
  // constructor is not defined. This is deleting the default copy const.
  Arena& operator=(const Arena& other) = delete;
  Arena(const Arena& other) = delete;

  // Dimensions of graphics window inside which players must operate
  double x_dim_;
  double y_dim_;
  unsigned int n_players_;
  unsigned int n_robots_;
  unsigned int n_obstacles_;
  double  batterylevel;

  // Other counters and iterators within the arena
  int wins;
  int losses;
  bool win;
  bool loss;
  int i;
  int j;
  int r;
  int s;
  int deleted;


  // Entities populating the arena
  Player* player_;
  RechargeStation * recharge_station_;
  HomeBase* home_base_;
  const struct arena_params* const initial_params;

  std::vector<class ArenaEntity*> entities_;
  std::vector<class ArenaMobileEntity*> mobile_entities_;
  std::vector<class Robot*> robots_;
  std::vector<class SuperBot*> superbots_;
  std::vector<class SensorTouch*> sensors_t_;
  std::vector<class SensorProximity*> sensors_p_;
  std::vector<class SensorEntityType*> sensors_e_;
  std::vector<class SensorDistress*> sensors_d_;
};

NAMESPACE_END(csci3081);

#endif  // SRC_ARENA_H_
