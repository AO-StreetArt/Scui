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

#ifndef SRC_WIDGET_LABEL_H_
#define SRC_WIDGET_LABEL_H_

namespace Scui {

//! A Label displays a piece of text
class Label : virtual public Widget {
  std::string _text;
  int _size;
  std::string _font_texture_file;
 public:
  ~Label() {}
  Label() {Widget::set_widget_type(LABEL_WIDGET);}

  //! Set the label text
  void set_text(std::string new_text) {_text = new_text;}

  //! Get the label text
  std::string get_text() {return _text;}

  //! Set the text size
  void set_size(int new_size) {_size = new_size;}

  //! Get the text size
  int get_size() {return _size;}

  //! Set the font texture file
  void set_font_texture(std::string new_font) {_font_texture_file = new_font;}

  //! Get the font texture file
  std::string get_font_texture() {return _font_texture_file;}

  //! Update the Widget

  //! Do nothing intentionally
  //! Non-layouts can leave this method blank
  void update() {}
};

}  // namespace Scui

#endif  // SRC_WIDGET_LABEL_H_
