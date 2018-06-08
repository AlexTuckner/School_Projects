/**
 * @file graphics_arena_viewer.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/graphics_arena_viewer.h"
#include <iostream>
#include <string>
#include <vector>

#include "src/robot.h"
#include "src/home_base.h"
#include "src/obstacle.h"
#include "src/arena_params.h"
#include "src/event_keypress.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
GraphicsArenaViewer::GraphicsArenaViewer(
  const struct arena_params* const params)
    : csci3081::GraphicsApp(params->x_dim, params->y_dim, "Robot Simulation"),
      arena_(new Arena(params)),
      paused_(false),
      pause_btn_(nullptr),
      last_dt(-1) {
  gui = new nanogui::FormHelper(this);
  new_gui = new nanogui::FormHelper(this);
  nanogui::ref<nanogui::Window> window =
            gui->addWindow(Eigen::Vector2i(1044, 20), "Simulation Controls");
  gui->addButton("Restart",
    std::bind(&GraphicsArenaViewer::OnRestartBtnPressed, this));
  pause_btn_ = gui->addButton("Pause",
    std::bind(&GraphicsArenaViewer::OnPauseBtnPressed, this));

  nanogui::ref<nanogui::Window> new_window =
        new_gui->addWindow(Eigen::Vector2i(1044, 150), "Game Status");

  // These add the new-gui which contains Battery, Wins, and Losses
  new_gui->addVariable("Battery", robot_battery_level)->setEditable(true);
  new_gui->addVariable("Wins: ", num_Wins)->setEditable(true);
  new_gui->addVariable("Losses: ", num_Losses)->setEditable(true);


  last_dt = 0;
  performLayout();
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

// This is the primary driver for state change in the arena.
// It will be called at each iteration of nanogui::mainloop()
void GraphicsArenaViewer::UpdateSimulation(double dt) {
  if (!paused_) {
    if ((last_dt + dt) > .05) {
      arena_->AdvanceTime(dt+last_dt);
      last_dt = 0;
      robot_battery_level = floor(arena_->get_battery_level());
      num_Wins = arena_->get_wins();
      num_Losses = arena_->get_loss();
      new_gui->refresh();
    } else {
      last_dt += dt;
    }
  }
}

/*******************************************************************************
 * Handlers for User Keyboard and Mouse Events
 ******************************************************************************/
void GraphicsArenaViewer::OnRestartBtnPressed() {
  arena_->Reset();
}

void GraphicsArenaViewer::OnPauseBtnPressed() {
  paused_ = !paused_;
  if (paused_) {
    pause_btn_->setCaption("Play");
  } else {
    pause_btn_->setCaption("Pause");
  }
}

void GraphicsArenaViewer::OnMouseMove(int x, int y) {}

void GraphicsArenaViewer::OnLeftMouseDown(int x, int y) {}

void GraphicsArenaViewer::OnLeftMouseUp(int x, int y) {}

void GraphicsArenaViewer::OnRightMouseDown(int x, int y) {}

void GraphicsArenaViewer::OnRightMouseUp(int x, int y) {}

void GraphicsArenaViewer::OnKeyDown(const char *c, int modifiers) {}

void GraphicsArenaViewer::OnKeyUp(const char *c, int modifiers) {}

void GraphicsArenaViewer::OnSpecialKeyDown(int key, int scancode,
  int modifiers) {
  EventKeypress e(key);
  // arena_->Accept(&e);
  //          << " modifiers=" << modifiers << std::endl;
  switch (key) {
    case GLFW_KEY_UP:
    case GLFW_KEY_DOWN:
    case GLFW_KEY_LEFT:
    case GLFW_KEY_RIGHT:
      arena_->Accept(&e);
      break;
  }
}

void GraphicsArenaViewer::OnSpecialKeyUp(int key, int scancode,
                          int modifiers) {}

/*******************************************************************************
 * Drawing of Entities in Arena
 ******************************************************************************/
void GraphicsArenaViewer::DrawRobot(NVGcontext *ctx, const Robot* const robot) {
  // translate and rotate all graphics calls that follow so that they are
  // centered, at the position and heading for this robot
  nvgSave(ctx);
  nvgTranslate(ctx, robot->get_pos().x(), robot->get_pos().y());
  nvgRotate(ctx, robot->heading_angle());

  // robot's circle
  nvgBeginPath(ctx);
  nvgCircle(ctx, 0.0, 0.0, robot->radius());
  nvgFillColor(ctx, nvgRGBA(static_cast<int>(robot->get_color().r),
                            static_cast<int>(robot->get_color().g),
                            static_cast<int>(robot->get_color().b),
                            255));
  nvgFill(ctx);
  nvgStrokeColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgStroke(ctx);

  // robot id text label
  nvgSave(ctx);
  nvgRotate(ctx, M_PI / 2.0);
  nvgFillColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgText(ctx, 0.0, 10.0, robot->get_name().c_str(), NULL);
  nvgRestore(ctx);

  nvgRestore(ctx);
}

void GraphicsArenaViewer::DrawObstacle(NVGcontext *ctx,
                                       const Obstacle* const obstacle) {
  nvgBeginPath(ctx);
  nvgCircle(ctx, obstacle->get_pos().x(), obstacle->get_pos().y(),
            obstacle->radius());
  nvgFillColor(ctx, nvgRGBA(static_cast<int>(obstacle->get_color().r),
                            static_cast<int>(obstacle->get_color().g),
                            static_cast<int>(obstacle->get_color().b),
                            255));
  nvgFill(ctx);
  nvgStrokeColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgStroke(ctx);

  nvgFillColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgText(ctx, obstacle->get_pos().x(), obstacle->get_pos().y(),
          obstacle->get_name().c_str(), NULL);
}

void GraphicsArenaViewer::DrawHomeBase(NVGcontext *ctx,
                               const HomeBase* const home) {
  nvgBeginPath(ctx);
  nvgCircle(ctx, home->get_pos().x(), home->get_pos().y(), home->radius());
  nvgFillColor(ctx, nvgRGBA(static_cast<int>(home->get_color().r),
                            static_cast<int>(home->get_color().g),
                            static_cast<int>(home->get_color().b),
                            255));
  nvgFill(ctx);
  nvgStrokeColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgStroke(ctx);

  nvgFillColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgText(ctx, home->get_pos().x(), home->get_pos().y(),
          home->get_name().c_str(), NULL);
}

void GraphicsArenaViewer::DrawUsingNanoVG(NVGcontext *ctx) {
  // initialize text rendering settings
  nvgFontSize(ctx, 18.0f);
  nvgFontFace(ctx, "sans-bold");
  nvgTextAlign(ctx, NVG_ALIGN_CENTER | NVG_ALIGN_MIDDLE);

  std::vector<Obstacle*> obstacles = arena_->obstacles();
  for (size_t i = 0; i < obstacles.size(); i++) {
    DrawObstacle(ctx, obstacles[i]);
  } /* for(i..) */

  DrawRobot(ctx, arena_->robot());
  DrawHomeBase(ctx, arena_->home_base());
}

NAMESPACE_END(csci3081);
