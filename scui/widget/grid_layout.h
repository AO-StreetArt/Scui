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

#include "scui/event/interface/mouse_event_interface.h"
#include "scui/event/interface/keyboard_event_interface.h"

#include "scui/widget/interface/widget_interface.h"
#include "scui/widget/widget.h"
#include "scui/widget/layout.h"

#ifndef SRC_WIDGET_GRID_LAYOUT_H_
#define SRC_WIDGET_GRID_LAYOUT_H_

namespace Scui {

//! An Layout contains children widgets and organizes them
class GridLayout : public Layout {
  int _rows = 0;
  int _cols = 0;
 public:
  ~GridLayout() {}
  GridLayout() {Widget::set_widget_type(GRIDLAYOUT_WIDGET);}

  //! Set the number of rows in the layout
  void set_rows(int new_rows) {_rows = new_rows;}

  //! Get the number of rows in the layout
  int get_rows() {return _rows;}

  //! Set the number of columns in the layout
  void set_columns(int new_cols) {_cols = new_cols;}

  //! Get the number of columns in the layout
  int get_columns() {return _cols;}

  //! Update the Widget

  //! A layout, when calling update, aligns it's children elements
  //! correctly, setting their x, y, width, and height values before calling
  //! their respective draw() functions.
  inline void update() {
    int current_row = 0;
    int current_col = 0;
    if (((_rows * _cols) < Widget::num_children()) || \
      _rows == 0 || _cols == 0) {
      // Throw an exception for invalid rows/cols
      throw WidgetException("Invalid number of Rows and/or Columns.");
    }
    for (int i = 0; i < Widget::num_children(); i++) {
      // Set the x value of the child
      Widget::get_child(i)->set_x((current_col * (Widget::get_width() / _cols)) + Widget::get_x());
      // Set the y value of the child
      Widget::get_child(i)->set_y((current_row * (Widget::get_height() / _rows)) + Widget::get_y());
      // Set the width value of the child
      Widget::get_child(i)->set_width(Widget::get_width() / _cols);
      // Set the height value of the child
      Widget::get_child(i)->set_height(Widget::get_height() / _rows);
      // Call the draw() function of the child
      Widget::get_child(i)->update();
      current_col++;
      if (current_col == _cols) {
        current_col = 0;
        current_row++;
      }
    }
  }
};

}  // namespace Scui

#endif  // SRC_WIDGET_GRID_LAYOUT_H_
