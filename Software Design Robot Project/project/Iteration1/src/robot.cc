/**
 * @file robot.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/robot.h"
#include "src/robot_motion_behavior.h"
#include "src/event_command.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Static Variables
 ******************************************************************************/
uint Robot::next_id_ = 0;

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Robot::Robot(const struct robot_params* const params) :
  ArenaMobileEntity(params->radius, params->collision_delta,
                    params->pos, params->color),
  id_(-1),
  // heading_angle_(0),
  // angle_delta_(params->angle_delta),
  battery_(params->battery_max_charge),
  motion_handler_(),
  motion_behavior_(),
  sensor_touch_() {
  motion_handler_.heading_angle(90);
  motion_handler_.speed(5);
  id_ = next_id_++;
  set_ent_Num(2);
  set_initial_Pos(params->pos);
}


/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void Robot::TimestepUpdate(uint dt) {
  if (sensor_touch_.activated()) {
    set_pos(get_Last_Position());
  } else {
  set_Second_Last_Position(get_Last_Position());
  set_Last_Position(get_pos());
  }
  Position old_pos = get_pos();
  // Update heading and speed as indicated by touch sensor
  motion_handler_.UpdateVelocity(sensor_touch_);

  // Use velocity and position to update position
  motion_behavior_.UpdatePosition(this, dt);

  // Deplete battery as appropriate given distance and speed of movement
  battery_.Deplete(old_pos, get_pos(), dt);
} /* TimestepUpdate() */

void Robot::Accept(const EventRecharge * const e) {
  battery_.EventRecharge();
}

  // Accept an event collision when a collision occurs
void Robot::Accept(const EventCollision * const e) {
  sensor_touch_.Accept(e);
  if (sensor_touch_.activated()) {
    motion_handler_.heading_angle(sensor_touch_.angle_of_contact());
    battery_.Accept(e);
    if (this->get_speed() > 3) {
      this->set_speed(this->get_speed() - 2);
    } else if (this->get_speed() == 0) {
    } else {
      this->set_speed(1);
    }
  }
}

  // Accept an EventCommand when the user presses a key
void Robot::Accept(const EventCommand * const e) {
  motion_handler_.AcceptCommand(e->cmd());
}

  // Take an enum event_commands cmd and send it to the motion hangler
void Robot::EventCmd(enum event_commands cmd) {
  motion_handler_.AcceptCommand(cmd);
} /* event_cmd() */

  // Reset the robot if "Reset" is pressed
void Robot::Reset(void) {
  battery_.Reset();
  motion_handler_.Reset();
  sensor_touch_.Reset();
  this->set_pos(this->get_initial_Pos());
} /* Reset() */

  // Reset the battery when "Reset" is pressed
void Robot::ResetBattery(void) {
  battery_.Reset();
}

NAMESPACE_END(csci3081);
