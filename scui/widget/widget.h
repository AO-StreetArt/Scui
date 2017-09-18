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

#include <vector>

#include "scui/event/interface/mouse_event_interface.h"
#include "scui/event/interface/keyboard_event_interface.h"

#include "scui/widget/interface/widget_interface.h"

#ifndef SRC_WIDGET_WIDGET_H_
#define SRC_WIDGET_WIDGET_H_

namespace Scui {

//! An Widget represents a single object within the GUI

//! Whether it is a layout, a pre-packaged UI element, or
//! a custom UI element.  All UI elements should implement
//! this interface.
class Widget : public WidgetInterface {
  int _x = 0;
  int _y = 0;
  int _width = 0;
  int _height = 0;
  std::vector<WidgetInterface*> _children;
  WidgetCallbackFunction _callback;
  bool _callback_registered = false;
  int _type = NULL_WIDGET;

 public:
  virtual ~Widget() {}

  void clear() \
    {for (unsigned int i = 0; i < _children.size(); i++) {delete _children[i];}}

  // Type
  //! Get the widget type
  int get_widget_type() {return _type;}
  //! Set the widget type
  void set_widget_type(int new_type) {_type = new_type;}

  // X/Y

  //! Get the x value for the pixel at the top left corner of the widget
  int get_x() {return _x;}
  //! Set the x value for the pixel at the top left corner of the widget
  void set_x(int new_x) {_x = new_x;}
  //! Get the y value for the pixel at the top left corner of the widget
  int get_y() {return _y;}
  //! Set the y value for the pixel at the top left corner of the widget
  void set_y(int new_y) {_y = new_y;}

  // Width/Height

  //! Get the width of the widget, in pixels
  int get_width() {return _width;}
  //! Set the width of the widget, in pixels
  void set_width(int new_width) {_width = new_width;}
  //! Get the height of the widget, in pixels
  int get_height() {return _height;}
  //! Set the height of the widget, in pixels
  void set_height(int new_height) {_height = new_height;}

  // Children

  //! Get a widget from the children list
  WidgetInterface* get_child(int index) {return _children[index];}
  //! Add a widget from the children list
  void add_child(WidgetInterface *new_child) {_children.push_back(new_child);}
  //! Get the number of widgets in the children list
  int num_children() {return _children.size();}
  //! Delete a child from the children list
  void remove_child(int index) {_children.erase(_children.begin() + index);}

  // Callback

  //! Set the widget callback
  inline void set_callback(WidgetCallbackFunction callback_func) {
    _callback = callback_func;
    _callback_registered = true;
  }
  //! Has a callback function been registered?
  bool has_callback() {return _callback_registered;}
  //! Call the widget callback
  inline void execute_callback(MouseEventInterface *mouse_event, \
    KeyboardEventInterface *keyboard_event) {
    // Execute the widget callback, if registered
    if (_callback_registered) (*(_callback))(mouse_event, keyboard_event);
    // Execute the callbacks of the children
    for (unsigned int i = 0; i < _children.size(); i++) {
      _children[i]->execute_callback(mouse_event, keyboard_event);
    }
  }

  //! Update the Widget in preparation for drawing
  virtual void update() = 0;

  //! Load the OpenGL Widget Components prior to the main loop
  virtual void load() = 0;

  //! Draw the Widget
  virtual void draw() = 0;
};

}  // namespace Scui

#endif  // SRC_WIDGET_WIDGET_H_
