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

#include "interface/mouse_event_interface.h"
#include "interface/keyboard_event_interface.h"

#include "interface/widget_interface.h"
#include "widget.h"

#ifndef SRC_WIDGET_LAYOUT_H_
#define SRC_WIDGET_LAYOUT_H_

namespace Scui {

//! An Layout contains children widgets and organizes them
class Layout : virtual public Widget {
 public:
  virtual ~Layout() {}

  //! Update the Widget

  //! A layout, when calling update, aligns it's children elements
  //! correctly, setting their x, y, width, and height values before calling
  //! their respective draw() functions.
  virtual void update() = 0;

  //! Load the OpenGL Widget Components prior to the main loop
  void load() {
    for (int i = 0; i < Widget::num_children(); i++) \
      {Widget::get_child(i)->load();}
  }

  //! Draw the Widget
  void draw() {
    for (int i = 0; i < Widget::num_children(); i++) \
      {Widget::get_child(i)->draw();}
  }
};

}  // namespace Scui

#endif  // SRC_WIDGET_LAYOUT_H_
