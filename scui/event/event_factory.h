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

#include "scui/event/keyboard_input_event.h"
#include "scui/event/mouse_input_event.h"

#ifndef SRC_EVENT_EVENT_FACTORY_H_
#define SRC_EVENT_EVENT_FACTORY_H_

namespace Scui {

// The Event Factory is used internally to build events
class EventFactory {
 public:
  EventFactory() {}
  ~EventFactory() {}
  // Build a mouse event
  MouseEventInterface* build_mouse_event(float x, float y, int but, int mods) \
    {return new MouseInputEvent(x, y, but, mods);}
  MouseEventInterface* build_mouse_event(double x, double y, int but, int mods) \
    {return build_mouse_event((float)x, (float)y, but, mods);}
  // Build a keyboard event
  // The key passed in must remain in-scope and valid for the duration of the
  // Event Interface
  KeyboardEventInterface* build_keyboard_event(char key, int mods) \
    {return new KeyboardInputEvent(key, mods);}
};

}  // namespace Scui

#endif  // SRC_EVENT_EVENT_FACTORY_H_
