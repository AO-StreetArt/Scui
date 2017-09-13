# Simple C++ UI Framework
The Simple C++ UI Framework, or Scui, is a barebones, minimal start of a UI framework in C++.  It relies only on OpenGL and glfw.

Please note that only a few widgets have been implemented, this is by no means a finished product.  However, it could be an excellent starting point for a more full-fledged UI framework.

## Usage
This library is headers-only, so using it is as simple as copying the src/ folder onto your include path.  Then, you'll use the following include flags:
    -I<scui_path>/event -I<scui_path>/widget -I<scui_path>/app

Please see the example for how to use the library.

## To-Do
Things that could be done to improve the library:
* Add more widgets, of course
* Add more layout widgets, specifically
* Allow user to design UI in YML/JSON, parse in application class and build the widget tree automatically
