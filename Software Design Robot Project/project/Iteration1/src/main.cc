/**
 * @file main.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/graphics_arena_viewer.h"
#include "src/arena_params.h"
#include "src/color.h"

/*******************************************************************************
 * Non-Member Functions
 ******************************************************************************/
int main(int, char **) {
  // Essential call to initiate the graphics window
  csci3081::InitGraphics();

  // Initialize default start values for various arena entities
  csci3081::robot_params rparams;

  rparams.battery_max_charge = 100.0;
  rparams.angle_delta = 10;
  rparams.collision_delta = 1;
  rparams.radius = 20.0;
  rparams.pos = Position(360, 250);
  rparams.color = csci3081::Color(0, 0, 255, 255); /* blue */

  csci3081::arena_params aparams;

  aparams.robot = rparams;

  aparams.recharge_station.radius = 20.0;
  aparams.recharge_station.pos = {500, 300};
  aparams.recharge_station.color = csci3081::Color(0, 128, 128, 255);
                                                  /* green */

  aparams.home_base.radius = 20.0;
  aparams.home_base.pos = {750, 500};
  aparams.home_base.color = csci3081::Color(255, 0, 0, 255); /* red */
  aparams.home_base.ent_Num = 1;

  aparams.obstacles[0].radius = 30.0;
  aparams.obstacles[0].pos = {200, 200};
  aparams.obstacles[0].color = csci3081::Color(255, 255, 255, 255); /* white */

  aparams.obstacles[1].radius = 30.0;
  aparams.obstacles[1].pos = {500, 60};
  aparams.obstacles[1].color = csci3081::Color(255, 255, 255, 255); /* white */

  aparams.obstacles[2].radius = 30.0;
  aparams.obstacles[2].pos = {300, 600};
  aparams.obstacles[2].color = csci3081::Color(255, 255, 255, 255); /* white */

  aparams.obstacles[3].radius = 30.0;
  aparams.obstacles[3].pos = {850, 250};
  aparams.obstacles[3].color = csci3081::Color(255, 255, 255, 255); /* white */

  aparams.obstacles[4].radius = 30.0;
  aparams.obstacles[4].pos = {700, 650};
  aparams.obstacles[4].color = csci3081::Color(255, 255, 255, 255); /* white */

  aparams.obstacles[5].radius = 30.0;
  aparams.obstacles[5].pos = {500, 400};
  aparams.obstacles[5].color = csci3081::Color(255, 255, 255, 255); /* white */

  aparams.n_obstacles = 6;
  aparams.x_dim = 1024 + 250;
  aparams.y_dim = 768;

  // Start up the graphics (which creates the arena).
  // Run will enter the nanogui::mainloop()
  csci3081::GraphicsArenaViewer *app =
      new csci3081::GraphicsArenaViewer(&aparams);
  app->Run();
  csci3081::ShutdownGraphics();
  return 0;
}
