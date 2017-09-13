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

#include <assert.h>

#include <iostream>

#include "interface/event_interface.h"
#include "interface/mouse_event_interface.h"
#include "interface/keyboard_event_interface.h"

#include "event_factory.h"

#include "interface/widget_interface.h"
#include "label.h"
#include "button.h"
#include "text_box.h"
#include "grid_layout.h"

// on_press callback function for the test button
void button_callback(Scui::MouseEventInterface* mouse_event, Scui::KeyboardEventInterface* keyboard_event) {
  if (mouse_event) {
    std::cout << "Press!" << std::endl;
    std::cout << mouse_event->get_x() << std::endl;
    std::cout << mouse_event->get_y() << std::endl;
  }
}

// on_release callback function for the test button
void release_callback(Scui::MouseEventInterface* mouse_event, Scui::KeyboardEventInterface* keyboard_event) {
  if (mouse_event) {
    std::cout << "Release!" << std::endl;
    std::cout << mouse_event->get_x() << std::endl;
    std::cout << mouse_event->get_y() << std::endl;
  }
}

// Set the base attributes of a widget
void set_base_attrs(Scui::WidgetInterface &widget, int x, int y, int width, int height) {
  widget.set_x(x);
  widget.set_y(y);
  widget.set_width(width);
  widget.set_height(height);
}

// Assert certain values for the base attributes of a widget
void base_widget_asserts(Scui::WidgetInterface &widget, int x, int y, int width, int height) {
  assert(widget.get_x() == x);
  assert(widget.get_y() == y);
  assert(widget.get_width() == width);
  assert(widget.get_height() == height);
}

// Print certain values for the base attributes of a widget
void print_base_widgets(Scui::WidgetInterface &widget) {
  std::cout << widget.get_x() << std::endl;
  std::cout << widget.get_y() << std::endl;
  std::cout << widget.get_width() << std::endl;
  std::cout << widget.get_height() << std::endl;
}

// Set the label-specific fields of a label or subclass
void set_label_attrs(Scui::Label &lbl, std::string &txt, std::string &ftexture, int size) {
  lbl.set_text(txt);
  lbl.set_font_texture(ftexture);
  lbl.set_size(size);
}

// Get the label-specific fields of a label or subclass
void label_widget_asserts(Scui::Label &lbl, std::string &txt, std::string &ftexture, int size) {
  assert(lbl.get_text() == txt);
  assert(lbl.get_font_texture() == ftexture);
  assert(lbl.get_size() == size);
}

// Main Test Function
int main(int argc, char** argv) {
  std::cout << "Starting Widget Test" << std::endl;

  // Build some mouse events to pass down the widget tree
  Scui::EventFactory factory;
  Scui::MouseEventInterface *mouse_event = \
    factory.build_mouse_event(111.0f, 221.0f, Scui::LEFT_MOUSE_DOWN_EVENT, Scui::ALT_MODIFIER);
  Scui::MouseEventInterface *mouse_event2 = \
    factory.build_mouse_event(1.0f, 2.0f, Scui::LEFT_MOUSE_UP_EVENT, Scui::ALT_MODIFIER);
  Scui::MouseEventInterface *mouse_event3 = \
    factory.build_mouse_event(321.0f, 232.0f, Scui::LEFT_MOUSE_DOWN_EVENT, Scui::SHIFT_MODIFIER);

  // Label Tests
  Scui::Label lbl;
  set_base_attrs(lbl, 100, 200, 300, 400);
  std::string label_text = "Testing";
  std::string font_texture_file = "testfile";
  set_label_attrs(lbl, label_text, font_texture_file, 35);
  base_widget_asserts(lbl, 100, 200, 300, 400);
  label_widget_asserts(lbl, label_text, font_texture_file, 35);

  // Basic Button Tests
  Scui::Button btn;
  set_base_attrs(btn, 110, 220, 330, 440);
  std::string label_text2 = "Testing2";
  std::string font_texture_file2 = "testfile1";
  set_label_attrs(btn, label_text2, font_texture_file2, 36);
  base_widget_asserts(btn, 110, 220, 330, 440);
  label_widget_asserts(btn, label_text2, font_texture_file2, 36);

  // Button-specific tests
  std::string pressed_texture = "testfile2";
  btn.set_pressed_texture(pressed_texture);
  std::string unpressed_texture = "testfile3";
  btn.set_unpressed_texture(unpressed_texture);
  btn.set_press_func(button_callback);
  btn.set_release_func(release_callback);
  assert(btn.get_pressed_texture() == "testfile2");
  assert(btn.get_unpressed_texture() == "testfile3");

  // Execute the button callback function
  // The first call should execute the on_press function
  btn.execute_callback(mouse_event, NULL);
  // The second call should execute the on_release function
  btn.execute_callback(mouse_event2, NULL);

  // Basic Textbox Tests
  Scui::TextBox tbx;
  set_base_attrs(tbx, 120, 230, 340, 450);
  std::string label_text3 = "Testing3";
  std::string font_texture_file3 = "testfile4";
  set_label_attrs(tbx, label_text3, font_texture_file3, 40);
  base_widget_asserts(tbx, 120, 230, 340, 450);
  label_widget_asserts(tbx, label_text3, font_texture_file3, 40);

  // TextBox-specific tests
  std::string active_texture = "testfile5";
  tbx.set_active_texture(active_texture);
  std::string inactive_texture = "testfile6";
  tbx.set_inactive_texture(inactive_texture);
  tbx.set_cursor_position(1);
  assert(tbx.get_active_texture() == "testfile5");
  assert(tbx.get_inactive_texture() == "testfile6");
  assert(tbx.get_cursor_position() == 1);

  // Layout Test

  // Create a layout
  Scui::GridLayout layout;
  set_base_attrs(layout, 100, 100, 400, 400);
  layout.set_rows(2);
  layout.set_columns(2);

  // Basic Tests
  base_widget_asserts(layout, 100, 100, 400, 400);
  assert(layout.get_rows() == 2);
  assert(layout.get_columns() == 2);

  // Add children to the layout
  layout.add_child(&lbl);
  layout.add_child(&btn);
  layout.add_child(&tbx);

  // Update the layout and test the children locations
  layout.update();

  print_base_widgets(layout);
  print_base_widgets(lbl);
  print_base_widgets(btn);
  print_base_widgets(tbx);

  assert(lbl.get_x() == 100);
  assert(lbl.get_y() == 100);
  assert(lbl.get_width() == 200);
  assert(lbl.get_height() == 200);

  assert(btn.get_x() == 300);
  assert(btn.get_y() == 100);
  assert(btn.get_width() == 200);
  assert(btn.get_height() == 200);

  assert(tbx.get_x() == 100);
  assert(tbx.get_y() == 300);
  assert(tbx.get_width() == 200);
  assert(tbx.get_height() == 200);

  // Call the layout callback, and ensure it cascades down the widget tree
  // The first call should execute the on_press function of the child button
  layout.execute_callback(mouse_event3, NULL);
  // The second call should execute the on_release function
  layout.execute_callback(mouse_event2, NULL);
  // The third call should not trigger any callbacks
  layout.execute_callback(mouse_event, NULL);

  std::cout << "Widget Test Completed" << std::endl;

  delete mouse_event;
  delete mouse_event2;
  delete mouse_event3;

  return 0;
}
