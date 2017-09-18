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

#include "scui/event/interface/mouse_event_interface.h"
#include "scui/event/interface/keyboard_event_interface.h"

#include "scui/widget/interface/widget_interface.h"
#include "scui/widget/widget.h"
#include "scui/widget/pressable.h"
#include "scui/widget/label.h"

#ifndef SRC_WIDGET_BUTTON_H_
#define SRC_WIDGET_BUTTON_H_

namespace Scui {

//! A Button displays a texture, with text overlaid.
class Button : public Pressable, public Label {
 public:
  ~Button() {}
  Button() {Widget::set_widget_type(BUTTON_WIDGET);}

  //! Update the Widget

  //! Do nothing intentionally
  //! Non-layouts can leave this method blank
  void update() {}

  //! TO-DO: Load the OpenGL Widget Components prior to the main loop
  void load() {
    for (int i = 0; i < Widget::num_children(); i++) \
      {Widget::get_child(i)->load();}
  }

  //! TO-DO: Draw the Widget
  void draw() {
    for (int i = 0; i < Widget::num_children(); i++) \
      {Widget::get_child(i)->draw();}
  }
};

}  // namespace Scui

#endif  // SRC_WIDGET_BUTTON_H_
