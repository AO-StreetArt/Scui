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

int main(int argc, char** argv) {
  std::cout << "Starting Event Test" << std::endl;
  // Setup
  Scui::EventFactory factory;

  // Keyboard Event Tests

  // Setup
  char key = 'a';
  Scui::KeyboardEventInterface *key_event = \
    factory.build_keyboard_event(Scui::_A_KEY, Scui::SHIFT_MODIFIER + Scui::CTRL_MODIFIER);

  // Asserts
  assert(key_event->get_key() == Scui::_A_KEY);
  assert(key_event->get_modifiers() == (Scui::SHIFT_MODIFIER + Scui::CTRL_MODIFIER));
  assert(key_event->get_modifiers() != (Scui::ALT_MODIFIER + Scui::CTRL_MODIFIER));
  assert(key_event->get_modifiers() != (Scui::ALT_MODIFIER + Scui::SHIFT_MODIFIER));
  assert(key_event->get_modifiers() != Scui::ALT_MODIFIER);
  assert(key_event->get_modifiers() != Scui::CTRL_MODIFIER);
  assert(key_event->get_modifiers() != Scui::SHIFT_MODIFIER);

  // Mouse Event Tests

  // Setup
  Scui::MouseEventInterface *mouse_event = \
    factory.build_mouse_event(1.0f, 2.0f, Scui::LEFT_MOUSE_DOWN_EVENT, Scui::ALT_MODIFIER);

  // Asserts
  assert(mouse_event->get_x() - 1.0f < 0.001f);
  assert(mouse_event->get_x() - 2.0f < 0.001f);
  assert(mouse_event->get_button() == Scui::LEFT_MOUSE_DOWN_EVENT);
  assert(mouse_event->get_modifiers() != (Scui::SHIFT_MODIFIER + Scui::CTRL_MODIFIER));
  assert(mouse_event->get_modifiers() != (Scui::ALT_MODIFIER + Scui::CTRL_MODIFIER));
  assert(mouse_event->get_modifiers() != (Scui::ALT_MODIFIER + Scui::SHIFT_MODIFIER));
  assert(mouse_event->get_modifiers() == Scui::ALT_MODIFIER);
  assert(mouse_event->get_modifiers() != Scui::CTRL_MODIFIER);
  assert(mouse_event->get_modifiers() != Scui::SHIFT_MODIFIER);

  // Cleanup
  delete key_event;
  delete mouse_event;

  std::cout << "Event Test Completed" << std::endl;

  return 0;
}
