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

#include <string>

#include "interface/mouse_event_interface.h"
#include "interface/keyboard_event_interface.h"

#include "interface/widget_interface.h"
#include "widget.h"

#ifndef SRC_WIDGET_PRESSABLE_H_
#define SRC_WIDGET_PRESSABLE_H_

namespace Scui {

//! An Layout contains children widgets and organizes them
class Pressable : virtual public Widget {
  std::string _pressed_texture_file;
  std::string _unpressed_texture_file;
  WidgetCallbackFunction _on_press;
  bool _press_func_registered = false;
  WidgetCallbackFunction _on_release;
  bool _release_func_registered = false;
  bool _is_active = false;
 public:
  virtual ~Pressable() {}

  //! Set the pressed texture file
  void set_pressed_texture(std::string new_file) {_pressed_texture_file = new_file;}

  //! Get the pressed texture file
  std::string get_pressed_texture() {return _pressed_texture_file;}

  //! Set the unpressed texture file
  void set_unpressed_texture(std::string new_file) {_unpressed_texture_file = new_file;}

  //! Get the unpressed texture file
  std::string get_unpressed_texture() {return _unpressed_texture_file;}

  //! Set the on_press function
  void set_press_func(WidgetCallbackFunction func) {_on_press = func; _press_func_registered = true;}

  //! Set the on_release function
  void set_release_func(WidgetCallbackFunction func) {_on_release = func; _release_func_registered = true;}

  //! Is the widget active (pressed down)
  bool is_active() {return _is_active;}

  //! If a mouse left click down is registered that is within our button,
  //! Then we will flip the active state.  When we get a mouse left click up,
  //! we reset the active state and return the button to normal
  inline void execute_callback(MouseEventInterface *mouse_event, \
    KeyboardEventInterface *keyboard_event) {
    // Do we have a mouse event?
    if (mouse_event) {
      // Check if the left mouse down is within the widget
      if ((mouse_event->get_button() == LEFT_MOUSE_DOWN_EVENT) && \
        (mouse_event->get_x() > Widget::get_x()) && \
        (mouse_event->get_x() < (Widget::get_x() + Widget::get_width())) && \
        (mouse_event->get_y() > Widget::get_y()) && \
        (mouse_event->get_y() < (Widget::get_y() + Widget::get_height()))) {
        // Set the active flag to true
        _is_active = true;
        // Call on_press function
        if (_press_func_registered) {
          (*(_on_press))(mouse_event, keyboard_event);
        }
      } else if ((mouse_event->get_button() == LEFT_MOUSE_UP_EVENT) && _is_active) {
        _is_active = false;
        // Call on_release function
        if (_release_func_registered) {
          (*(_on_release))(mouse_event, keyboard_event);
        }
      }
    }
  }
};

}  // namespace Scui

#endif  // SRC_WIDGET_PRESSABLE_H_
