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

#include "scui/event/interface/event_interface.h"
#include "scui/event/input_event.h"

#ifndef SRC_EVENT_INTERFACE_KEYBOARD_EVENT_INTERFACE_H_
#define SRC_EVENT_INTERFACE_KEYBOARD_EVENT_INTERFACE_H_

namespace Scui {

//! Key Constants
const int _NULL_KEY = -1;
const int _A_KEY = 0;
const int _B_KEY = 0;
const int _C_KEY = 0;
const int _D_KEY = 0;
const int _E_KEY = 0;
const int _F_KEY = 0;
const int _G_KEY = 0;
const int _H_KEY = 0;
const int _I_KEY = 0;
const int _J_KEY = 0;
const int _K_KEY = 0;
const int _L_KEY = 0;
const int _M_KEY = 0;
const int _N_KEY = 0;
const int _O_KEY = 0;
const int _P_KEY = 0;
const int _Q_KEY = 0;
const int _R_KEY = 0;
const int _S_KEY = 0;
const int _T_KEY = 0;
const int _U_KEY = 0;
const int _V_KEY = 0;
const int _W_KEY = 0;
const int _X_KEY = 0;
const int _Y_KEY = 0;
const int _Z_KEY = 0;
const int _SPACE_KEY = 0;
const int _TAB_KEY = 0;
const int _ESC_KEY = 0;
const int _DEL_KEY = 0;
const int _BKSP_KEY = 0;
const int _0_KEY = 0;
const int _1_KEY = 0;
const int _2_KEY = 0;
const int _3_KEY = 0;
const int _4_KEY = 0;
const int _5_KEY = 0;
const int _6_KEY = 0;
const int _7_KEY = 0;
const int _8_KEY = 0;
const int _9_KEY = 0;
const int _F1_KEY = 0;
const int _F2_KEY = 0;
const int _F3_KEY = 0;
const int _F4_KEY = 0;
const int _F5_KEY = 0;
const int _F6_KEY = 0;
const int _F7_KEY = 0;
const int _F8_KEY = 0;
const int _F9_KEY = 0;
const int _F10_KEY = 0;
const int _F11_KEY = 0;
const int _F12_KEY = 0;

//! An InputEvent is generated by a Mouse/Keyboard event
class KeyboardEventInterface : public EventInterface {
 public:
  virtual ~KeyboardEventInterface() {}
  //! Get the key associated with the event
  virtual int get_key() = 0;
};

}  // namespace Scui

#endif  // SRC_EVENT_INTERFACE_KEYBOARD_EVENT_INTERFACE_H_
