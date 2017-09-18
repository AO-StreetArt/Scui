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

#include <iostream>

#include "scui/event/interface/event_interface.h"
#include "scui/event/interface/mouse_event_interface.h"
#include "scui/event/interface/keyboard_event_interface.h"

#include "scui/widget/interface/widget_interface.h"
#include "scui/widget/label.h"
#include "scui/widget/grid_layout.h"

#include "scui/app/opengl_app.h"

// Escape callback function for the base layout to ensure we can exit
void escape_callback(Scui::MouseEventInterface* mouse_event, Scui::KeyboardEventInterface* keyboard_event) {
  if (keyboard_event) {
    if (keyboard_event->get_key() == Scui::_ESC_KEY) {
      throw Scui::WidgetException("Exit Requested.");
    }
  }
}

// Set the base attributes of a widget
void set_base_attrs(Scui::WidgetInterface &widget, int x, int y, int width, int height) {
  widget.set_x(x);
  widget.set_y(y);
  widget.set_width(width);
  widget.set_height(height);
}

// Set the label-specific fields of a label or subclass
void set_label_attrs(Scui::Label &lbl, std::string &txt, std::string &ftexture, int size) {
  lbl.set_text(txt);
  lbl.set_font_texture(ftexture);
  lbl.set_size(size);
}

// Main Test Function
int main(int argc, char** argv) {

  // Set up the OpenGL Application
  std::string app_title = "Hello World";
  Scui::application = new Scui::OpenglApp(app_title);

  // Label Tests
  Scui::Label lbl;
  set_base_attrs(lbl, 100, 200, 300, 400);
  std::string label_text = "Testing";
  std::string font_texture_file = "testfile";
  set_label_attrs(lbl, label_text, font_texture_file, 35);

  // Create a layout
  Scui::GridLayout layout;
  set_base_attrs(layout, 100, 100, 400, 400);
  layout.set_rows(2);
  layout.set_columns(2);

  // Add children to the layout
  layout.add_child(&lbl);

  // Set the callback of the layout so we can use the escape key to exit
  layout.set_callback(escape_callback);

  // Set the layout to the root of the app
  Scui::application->set_root(&layout);

  // Run the application
  try {
    Scui::application->run();
  }
  catch (std::exception& e) {
    std::cout << "Exception Encountered: " << e.what() << std::endl;
  }

  return 0;
}
