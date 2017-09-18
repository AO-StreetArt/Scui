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

#include "scui/event/event_factory.h"

#include "scui/widget/interface/widget_interface.h"

#ifndef SRC_APP_APP_H_
#define SRC_APP_APP_H_

namespace Scui {

//! A Scui App holds a Widget Tree, and is responsible for actually rendering
//! The UI that's been constructed
class App {
  WidgetInterface *_root = NULL;

 public:
  virtual ~App() {}
  //! Retrieve the root of the widget tree
  WidgetInterface* get_root() {return _root;}
  //! Set the root of the widget tree
  void set_root(WidgetInterface *new_root) {_root = new_root;}

  //! Run the application
  virtual void run() = 0;
};

}  // namespace Scui

#endif  // SRC_APP_APP_H_
