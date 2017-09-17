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

// Include GLFW
#include <GLFW/glfw3.h>

#include "event_factory.h"
#include "interface/event_interface.h"
#include "interface/mouse_event_interface.h"
#include "interface/keyboard_event_interface.h"

#include "interface/widget_interface.h"

#include "app.h"
#include "global_app.h"

#ifndef SRC_APP_OPENGL_CALLBACKS_H_
#define SRC_APP_OPENGL_CALLBACKS_H_

namespace Scui {

// Convert modifiers supplied from GLFW into Scui modifiers
int convert_modifiers(int mods) {
  int event_mods = NULL_MODIFIER;
  // We use bitwise operator to decipher the mods from glfw
  if (mods & GLFW_MOD_SHIFT) {
    event_mods += SHIFT_MODIFIER;
  } else if (mods & GLFW_MOD_ALT) {
    event_mods += ALT_MODIFIER;
  } else if (mods & GLFW_MOD_CONTROL) {
    event_mods += CTRL_MODIFIER;
  }
  return event_mods;
}

// Mouse Callback
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
  // Setup the Event Factory and a variable to hold the new Scui Event
  EventFactory efactory;
  int event_button = NULL_MOUSE_EVENT;

  // Retrieve the cursor position
  double xpos, ypos;
  glfwGetCursorPos(window, &xpos, &ypos);

  // Convert the GLFW Button and action into a Scui Event Type
  if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
    event_button = Scui::RIGHT_MOUSE_DOWN_EVENT;
  } else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
    event_button = Scui::LEFT_MOUSE_DOWN_EVENT;
  } else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) {
    event_button = Scui::RIGHT_MOUSE_UP_EVENT;
  } else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
    event_button = Scui::LEFT_MOUSE_UP_EVENT;
  } else if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS) {
    event_button = Scui::MIDDLE_MOUSE_DOWN_EVENT;
  } else if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_RELEASE) {
    event_button = Scui::MIDDLE_MOUSE_UP_EVENT;
  }

  // Convert the modifiers
  int event_mods = convert_modifiers(mods);

  // Generate a new event and send it into the application widget tree
  MouseEventInterface *mouse_event = \
    efactory.build_mouse_event(xpos, ypos, event_button, event_mods);

  application->get_root()->execute_callback(mouse_event, NULL);
  delete mouse_event;
}

// Keyboard Callback
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  // Setup the Event Factory and a variable to hold the new Scui Event
  EventFactory efactory;
  int event_key = _NULL_KEY;

  // Convert the button and action into the key
  if (key == GLFW_KEY_A && action == GLFW_PRESS) {event_key = Scui::_A_KEY;}
  else if (key == GLFW_KEY_B && action == GLFW_PRESS) {event_key = Scui::_B_KEY;}
  else if (key == GLFW_KEY_C && action == GLFW_PRESS) {event_key = Scui::_C_KEY;}
  else if (key == GLFW_KEY_D && action == GLFW_PRESS) {event_key = Scui::_D_KEY;}
  else if (key == GLFW_KEY_E && action == GLFW_PRESS) {event_key = Scui::_E_KEY;}
  else if (key == GLFW_KEY_F && action == GLFW_PRESS) {event_key = Scui::_F_KEY;}
  else if (key == GLFW_KEY_G && action == GLFW_PRESS) {event_key = Scui::_G_KEY;}
  else if (key == GLFW_KEY_H && action == GLFW_PRESS) {event_key = Scui::_H_KEY;}
  else if (key == GLFW_KEY_I && action == GLFW_PRESS) {event_key = Scui::_I_KEY;}
  else if (key == GLFW_KEY_J && action == GLFW_PRESS) {event_key = Scui::_J_KEY;}
  else if (key == GLFW_KEY_K && action == GLFW_PRESS) {event_key = Scui::_K_KEY;}
  else if (key == GLFW_KEY_L && action == GLFW_PRESS) {event_key = Scui::_L_KEY;}
  else if (key == GLFW_KEY_M && action == GLFW_PRESS) {event_key = Scui::_M_KEY;}
  else if (key == GLFW_KEY_N && action == GLFW_PRESS) {event_key = Scui::_N_KEY;}
  else if (key == GLFW_KEY_O && action == GLFW_PRESS) {event_key = Scui::_O_KEY;}
  else if (key == GLFW_KEY_P && action == GLFW_PRESS) {event_key = Scui::_P_KEY;}
  else if (key == GLFW_KEY_Q && action == GLFW_PRESS) {event_key = Scui::_Q_KEY;}
  else if (key == GLFW_KEY_R && action == GLFW_PRESS) {event_key = Scui::_R_KEY;}
  else if (key == GLFW_KEY_S && action == GLFW_PRESS) {event_key = Scui::_S_KEY;}
  else if (key == GLFW_KEY_T && action == GLFW_PRESS) {event_key = Scui::_T_KEY;}
  else if (key == GLFW_KEY_U && action == GLFW_PRESS) {event_key = Scui::_U_KEY;}
  else if (key == GLFW_KEY_V && action == GLFW_PRESS) {event_key = Scui::_V_KEY;}
  else if (key == GLFW_KEY_W && action == GLFW_PRESS) {event_key = Scui::_W_KEY;}
  else if (key == GLFW_KEY_X && action == GLFW_PRESS) {event_key = Scui::_X_KEY;}
  else if (key == GLFW_KEY_Y && action == GLFW_PRESS) {event_key = Scui::_Y_KEY;}
  else if (key == GLFW_KEY_Z && action == GLFW_PRESS) {event_key = Scui::_Z_KEY;}
  else if (key == GLFW_KEY_0 && action == GLFW_PRESS) {event_key = Scui::_0_KEY;}
  else if (key == GLFW_KEY_1 && action == GLFW_PRESS) {event_key = Scui::_1_KEY;}
  else if (key == GLFW_KEY_2 && action == GLFW_PRESS) {event_key = Scui::_2_KEY;}
  else if (key == GLFW_KEY_3 && action == GLFW_PRESS) {event_key = Scui::_3_KEY;}
  else if (key == GLFW_KEY_4 && action == GLFW_PRESS) {event_key = Scui::_4_KEY;}
  else if (key == GLFW_KEY_5 && action == GLFW_PRESS) {event_key = Scui::_5_KEY;}
  else if (key == GLFW_KEY_6 && action == GLFW_PRESS) {event_key = Scui::_6_KEY;}
  else if (key == GLFW_KEY_7 && action == GLFW_PRESS) {event_key = Scui::_7_KEY;}
  else if (key == GLFW_KEY_8 && action == GLFW_PRESS) {event_key = Scui::_8_KEY;}
  else if (key == GLFW_KEY_9 && action == GLFW_PRESS) {event_key = Scui::_9_KEY;}
  else if (key == GLFW_KEY_F1 && action == GLFW_PRESS) {event_key = Scui::_F1_KEY;}
  else if (key == GLFW_KEY_F2 && action == GLFW_PRESS) {event_key = Scui::_F2_KEY;}
  else if (key == GLFW_KEY_F3 && action == GLFW_PRESS) {event_key = Scui::_F3_KEY;}
  else if (key == GLFW_KEY_F4 && action == GLFW_PRESS) {event_key = Scui::_F4_KEY;}
  else if (key == GLFW_KEY_F5 && action == GLFW_PRESS) {event_key = Scui::_F5_KEY;}
  else if (key == GLFW_KEY_F6 && action == GLFW_PRESS) {event_key = Scui::_F6_KEY;}
  else if (key == GLFW_KEY_F7 && action == GLFW_PRESS) {event_key = Scui::_F7_KEY;}
  else if (key == GLFW_KEY_F8 && action == GLFW_PRESS) {event_key = Scui::_F8_KEY;}
  else if (key == GLFW_KEY_F9 && action == GLFW_PRESS) {event_key = Scui::_F9_KEY;}
  else if (key == GLFW_KEY_F10 && action == GLFW_PRESS) {event_key = Scui::_F10_KEY;}
  else if (key == GLFW_KEY_F11 && action == GLFW_PRESS) {event_key = Scui::_F11_KEY;}
  else if (key == GLFW_KEY_F12 && action == GLFW_PRESS) {event_key = Scui::_F12_KEY;}
  else if (key == GLFW_KEY_BACKSPACE && action == GLFW_PRESS) {event_key = Scui::_BKSP_KEY;}
  else if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {event_key = Scui::_ESC_KEY;}
  else if (key == GLFW_KEY_DELETE && action == GLFW_PRESS) {event_key = Scui::_DEL_KEY;}
  else if (key == GLFW_KEY_TAB && action == GLFW_PRESS) {event_key = Scui::_TAB_KEY;}
  else if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {event_key = Scui::_SPACE_KEY;}

  // Convert the modifiers
  int event_mods = convert_modifiers(mods);

  // Create a new Scui Event
  Scui::KeyboardEventInterface *key_event = \
    efactory.build_keyboard_event(event_key, event_mods);

  // Execute the callbacks in the widget tree
  application->get_root()->execute_callback(NULL, key_event);
  delete key_event;
}

// Scroll Callback
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
  // Setup the Event Factory and a variable to hold the new Scui Event
  EventFactory efactory;
  int event_button = Scui::NULL_MOUSE_EVENT;

  if (yoffset > 0) {
    event_button = Scui::SCROLL_UP_EVENT;
  } else if (yoffset < 0) {
    event_button = Scui::SCROLL_DOWN_EVENT;
  }

  // Generate a new event and send it into the application widget tree
  MouseEventInterface *mouse_event = \
    efactory.build_mouse_event(0.0, yoffset, event_button, 0);

  application->get_root()->execute_callback(mouse_event, NULL);
  delete mouse_event;
}

}  // namespace Scui

#endif  // SRC_APP_OPENGL_CALLBACKS_H_
