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

#ifndef SRC_WIDGET_INTERFACE_WIDGET_INTERFACE_H_
#define SRC_WIDGET_INTERFACE_WIDGET_INTERFACE_H_

namespace Scui {

//! A Typedef representing a callback for a widget
typedef void(*WidgetCallbackFunction)(MouseEventInterface*, KeyboardEventInterface*);

//! Const Definitions for Instantiable Widget Types

//! NULL Widget Type
const int NULL_WIDGET = -1;

//! Widget Type for Grid Layouts
const int GRIDLAYOUT_WIDGET = 0;

//! Button Widget Type
const int BUTTON_WIDGET = 1;

//! Label Widget Type
const int LABEL_WIDGET = 2;

//! Text Box Widget Type
const int TEXTBOX_WIDGET = 3;

//! Widget Exception

//! A child class of std::exception
//! which holds error information
struct WidgetException: public std::exception {
  // An error message passed on initialization
  std::string int_msg;
  const char * int_msg_cstr;

  // Create a Widget Exception, and store the given error message
  inline WidgetException(std::string msg) {
    int_msg = "Error in Widget: " + msg;
    int_msg_cstr = int_msg.c_str();
  }

  WidgetException() {}
  ~WidgetException() throw() {}
  // Show the error message in readable format
  const char * what() const throw() {
    return int_msg_cstr;
  }
};

//! An Widget represents a single object within the GUI

//! Whether it is a layout, a pre-packaged UI element, or
//! a custom UI element.  All UI elements should implement
//! this interface.
class WidgetInterface {
 public:
  virtual ~WidgetInterface() {}

  // Widget Type

  //! Get the widget type
  virtual int get_widget_type() = 0;
  //! Set the widget type
  virtual void set_widget_type(int new_type) = 0;

  // X/Y

  //! Get the x value for the pixel at the top left corner of the widget
  virtual int get_x() = 0;
  //! Set the x value for the pixel at the top left corner of the widget
  virtual void set_x(int new_x) = 0;
  //! Get the y value for the pixel at the top left corner of the widget
  virtual int get_y() = 0;
  //! Set the y value for the pixel at the top left corner of the widget
  virtual void set_y(int new_y) = 0;

  // Width/Height

  //! Get the width of the widget, in pixels
  virtual int get_width() = 0;
  //! Set the width of the widget, in pixels
  virtual void set_width(int new_width) = 0;
  //! Get the height of the widget, in pixels
  virtual int get_height() = 0;
  //! Set the height of the widget, in pixels
  virtual void set_height(int new_height) = 0;

  // Children

  //! Get a widget from the children list
  virtual WidgetInterface* get_child(int index) = 0;
  //! Add a widget from the children list
  virtual void add_child(WidgetInterface *new_child) = 0;
  //! Get the number of widgets in the children list
  virtual int num_children() = 0;
  //! Delete a child from the children list
  virtual void remove_child(int index) = 0;

  // Callback

  //! Set the widget callback
  virtual void set_callback(WidgetCallbackFunction callback_func) = 0;
  //! Has a callback function been registered?
  virtual bool has_callback() = 0;
  //! Call the widget callback
  virtual void execute_callback(MouseEventInterface *mouse_event, \
    KeyboardEventInterface *keyboard_event) = 0;

  //! Update the Widget in preparation for drawing
  virtual void update() = 0;

  //! Load the OpenGL Widget Components prior to the main loop
  virtual void load() = 0;

  //! Draw the Widget
  virtual void draw() = 0;

  //! Delete the children in the list, only to be used if the children were
  //! allocated using new
  virtual void clear() = 0;
};

}  // namespace Scui

#endif  // SRC_WIDGET_INTERFACE_WIDGET_INTERFACE_H_
