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
#include "label.h"

#ifndef SRC_WIDGET_TEXT_BOX_H_
#define SRC_WIDGET_TEXT_BOX_H_

namespace Scui {

//! A Label displays a piece of text
class TextBox : public Label {
  std::string _ghost;
  std::string _active_texture;
  std::string _inactive_texture;
  bool _is_active = false;
  int _cursor_pos = 0;
 public:
  ~TextBox() {}
  TextBox() {Widget::set_widget_type(TEXTBOX_WIDGET);}

  //! Set the ghost text
  void set_ghost(std::string new_text) {_ghost = new_text;}

  //! Get the ghost text
  std::string get_ghost() {return _ghost;}

  //! Set the active texture location
  void set_active_texture(std::string new_texture) {_active_texture = new_texture;}

  //! Get the active texture location
  std::string get_active_texture() {return _active_texture;}

  //! Set the inactive texture location
  void set_inactive_texture(std::string new_texture) {_inactive_texture = new_texture;}

  //! Get the inactive texture location
  std::string get_inactive_texture() {return _inactive_texture;}

  //! Get the cursor position
  int get_cursor_position() {return _cursor_pos;}

  //! Set the cursor position
  void set_cursor_position(int new_pos) {_cursor_pos = new_pos;}

  //! Is the Text Box Active?
  bool is_active() {return _is_active;}

  //! If a mouse left click down is registered that is within our text box,
  //! Then we will flip the active state.  When we get a mouse left click down
  //! anywhere else, we reset the active state and return the box to normal
  inline void execute_callback(MouseEventInterface *mouse_event, \
    KeyboardEventInterface *keyboard_event) {
    // Do we have a mouse event?
    if (mouse_event) {
      // Check if the left mouse down is within the widget
      if (mouse_event->get_button() == LEFT_MOUSE_DOWN_EVENT) {
        if ((mouse_event->get_x() > Widget::get_x()) && \
          (mouse_event->get_x() < (Widget::get_x() + Widget::get_width())) && \
          (mouse_event->get_y() > Widget::get_y()) && \
          (mouse_event->get_y() < (Widget::get_y() + Widget::get_height()))) {
          // Set the active flag to true
          _is_active = true;
        } else {
          // Set the active flag to false
          _is_active = true;
        }
      }
    } else if (keyboard_event) {
      // TO-DO: Handle Keyboard Events
    }
    // Execute our callback, if present, and those of any children, if present
    Widget::execute_callback(mouse_event, keyboard_event);
  }

  //! Update the Widget

  //! Do nothing intentionally
  //! Non-layouts can leave this method blank
  void update() {}
};

}  // namespace Scui

#endif  // SRC_WIDGET_TEXT_BOX_H_
