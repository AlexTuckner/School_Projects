/**
 * @file player.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/player.h"
#include "src/event_command.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Static Variables
 ******************************************************************************/
uint Player::next_id_ = 0;

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Player::Player(const struct player_params* const params) :
  ArenaMobileEntity(params->radius, kPlayer, params->collision_delta,
                    params->pos, params->color),
  id_(-1),
  // heading_angle_(0),
  // angle_delta_(params->angle_delta),
  battery_(params->battery_max_charge),
  motion_handler_player_(90, 5),
  player_motion_behavior_(),
  sensor_touch_(kPlayer, 0, Position(0, 0), 0),
  frozen(false),
  frozen_time(100) {
  id_ = next_id_++;
  set_ent_Num(2);
  set_initial_Pos(params->pos);
}


/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void Player::TimestepUpdate(uint dt) {
  if (sensor_touch_.get_is_activated()) {
    set_pos(get_Last_Position());
    battery_.hit_obect();
    motion_handler_player_.AcceptCollision(sensor_touch_);
    sensor_touch_.set_is_activated(false);
  } else {
  set_Second_Last_Position(get_Last_Position());
  set_Last_Position(get_pos());
  }
  Position old_pos = get_pos();
  // Update heading and speed as indicated by touch sensor
  motion_handler_player_.UpdateVelocity(sensor_touch_);

  // Use velocity and position to update position
  player_motion_behavior_.UpdatePosition(this, dt);

  // Deplete battery as appropriate given distance and speed of movement
  battery_.Deplete(old_pos, get_pos(), dt);

  if (get_frozen()) {
    set_speed(0);
  }
} /* TimestepUpdate() */

void Player::Accept(const EventRecharge * const e) {
  battery_.EventRecharge();
}

  // Accept an event collision when a collision occurs
void Player::Accept(const EventCollision * const e) {}

  // Accept an EventCommand when the user presses a key
void Player::Accept(const EventCommand * const e) {
  motion_handler_player_.AcceptCommand(e->cmd());
}

  // Take an enum event_commands cmd and send it to the motion hangler
void Player::EventCmd(enum event_commands cmd) {
  motion_handler_player_.AcceptCommand(cmd);
} /* event_cmd() */

  // Reset the player if "Reset" is pressed
void Player::Reset(void) {
  battery_.Reset();
  motion_handler_player_.Reset();
  sensor_touch_.Reset();
  this->set_pos(this->get_initial_Pos());
} /* Reset() */

  // Reset the battery when "Reset" is pressed
void Player::ResetBattery(void) {
  battery_.Reset();
}

NAMESPACE_END(csci3081);
