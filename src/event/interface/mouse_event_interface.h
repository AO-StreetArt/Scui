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

#include "event_interface.h"
#include "input_event.h"

#ifndef SRC_EVENT_INTERFACE_MOUSE_EVENT_INTERFACE_H_
#define SRC_EVENT_INTERFACE_MOUSE_EVENT_INTERFACE_H_

namespace Scui {

//! Un-assigned button
const int NULL_MOUSE_EVENT = -1;

//! Left Mouse Button
const int LEFT_MOUSE_DOWN_EVENT = 0;

//! Right Mouse Button
const int RIGHT_MOUSE_DOWN_EVENT = 1;

//! Middle Mouse Button
const int MIDDLE_MOUSE_DOWN_EVENT = 2;

//! Left Mouse Button
const int LEFT_MOUSE_UP_EVENT = 3;

//! Right Mouse Button
const int RIGHT_MOUSE_UP_EVENT = 4;

//! Middle Mouse Button
const int MIDDLE_MOUSE_UP_EVENT = 5;

//! Mouse Scroll Up
const int SCROLL_UP_EVENT = 6;

//! Mouse Scroll Down
const int SCROLL_DOWN_EVENT = 7;

//! A Mouse Event is generated only by mouse updates
class MouseEventInterface : public EventInterface {
 public:
  virtual ~MouseEventInterface() {}
  //! Get the X Position of the Mouse at the time of the event
  virtual float get_x() = 0;
  //! Get the Y Position of the Mouse at the time of the event
  virtual float get_y() = 0;
  //! Get the Mouse Button, if any, associated to the event
  virtual int get_button() = 0;
};

}  // namespace Scui

#endif  // SRC_EVENT_INTERFACE_MOUSE_EVENT_INTERFACE_H_
