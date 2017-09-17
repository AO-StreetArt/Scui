/*
Apache2 License Notice
Copyright 2017 Alex Barry

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "event_factory.h"
#include "interface/event_interface.h"
#include "interface/mouse_event_interface.h"
#include "interface/keyboard_event_interface.h"

#include "interface/widget_interface.h"

#include "app.h"
#include "global_app.h"
#include "opengl_callbacks.h"
#include "opengl_utils.h"

#ifndef SRC_APP_OPENGL_APP_H_
#define SRC_APP_OPENGL_APP_H_

namespace Scui {

//! A Scui App holds a Widget Tree, and is responsible for actually rendering
//! The UI that's been constructed.  The opengl app uses opengl to do this
class OpenglApp : public App {
  // Internal Variables
  std::string _app_name = "My Scui App";

  // Start up OpenGL
  inline void init_opengl() {
    // Initialize glfw
    if (!glfwInit()) {
      throw OpenGlAppException("Error Initializing GLFW");
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    // Force us to use version 3.3 of opengl
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Mac OS Fix
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create the window
    window = glfwCreateWindow (1024, 768, _app_name.c_str(), NULL, NULL);
    if(!window) {
      glfwTerminate();
      throw OpenGlAppException("Error Creating Window");
    }

    // Create the OpenGL Context
    glfwMakeContextCurrent(window);

    // Initialize glew
    // Needed for core profile (not sure why)
    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
      glfwTerminate();
      throw OpenGlAppException("Error Initializing GLEW");
    }

    // Set the background color
    glClearColor(0.0f, 0.0f, 0.1f, 0.0f);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Set the mouse at the center of the screen
    glfwPollEvents();
    glfwSetCursorPos(window, 1024/2, 768/2);

    // Bind our callbacks
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetKeyCallback(window, key_callback);
  }

 public:
  OpenglApp() {application = this;}
  OpenglApp(std::string title) {_app_name = title; application = this;}
  ~OpenglApp() {glfwTerminate();}

  //! Run the application
  inline void run() {
    // Initialize OpenGL
    init_opengl();

    // Start by updating the widget tree to get initial positions
    App::get_root()->update();

    // Then load the GL components we can for each widget prior to the main loop
    App::get_root()->load();

    // Central Loop
    while (true) {
      // Clear the screen
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      // call update() and draw() for the widget tree
      App::get_root()->update();
      App::get_root()->draw();

      // Swap buffers
      glfwSwapBuffers(window);
      glfwPollEvents();
    }
  }
};

}  // namespace Scui

#endif  // SRC_APP_OPENGL_APP_H_
