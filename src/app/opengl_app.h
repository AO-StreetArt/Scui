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


#include "event_factory.h"
#include "interface/event_interface.h"
#include "interface/mouse_event_interface.h"
#include "interface/keyboard_event_interface.h"

#include "interface/widget_interface.h"

#include "app.h"

#ifndef SRC_APP_OPENGL_APP_H
#define SRC_APP_OPENGL_APP_H

namespace Scui {

//! A Scui App holds a Widget Tree, and is responsible for actually rendering
//! The UI that's been constructed.  The opengl app uses opengl to do this
class OpenglApp : public App {
 public:
  OpenglApp() {}
  ~OpenglApp() {}
  //! Run the application
  void run() {}
};

}  // namespace Scui

#endif  // SRC_APP_OPENGL_APP_H
