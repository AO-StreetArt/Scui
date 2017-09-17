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

#include "opengl_utils.h"

#ifndef SRC_WIDGET_LABEL_H_
#define SRC_WIDGET_LABEL_H_

namespace Scui {

//! A Label displays a piece of text
class Label : virtual public Widget {
  // Publicly exposed attributes
  std::string _text;
  int _size;
  std::string _font_texture_file = "/usr/local/share/scui/asset/texture/text/TNR.bmp";

  // Private attributes
  GLuint text_textureID;
  GLuint text_vboID;
  GLuint text_uvID;
  GLuint text_shaderID;
  GLuint text_uniformID;
 public:
  inline ~Label() {
    glDeleteBuffers(1, &text_vboID);
    glDeleteBuffers(1, &text_vboID);
    glDeleteTextures(1, &text_uvID);
    glDeleteProgram(text_shaderID);
  }
  inline Label() {Widget::set_widget_type(LABEL_WIDGET);}

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

  //! Load the OpenGL Widget Components prior to the main loop
  inline void load() {
    // Load the Texture file
    text_textureID = load_texture(_font_texture_file);

    // Initialize the VBO
    glGenBuffers(1, &text_vboID);
    glGenBuffers(1, &text_uvID);

    // Setup the shaders
    text_shaderID = \
      compile_shaders("/usr/local/share/scui/asset/shader/text/text_vertex_shader.glsl", \
                      "/usr/local/share/scui/asset/shader/text/text_fragment_shader.glsl")

    // Initialize the handle to the texture sampler
    text_uniformID = glGetUniformLocation(text_shaderID, "myTextureSampler");

    // Load the children
    for (int i = 0; i < Widget::num_children(); i++) \
      {Widget::get_child(i)->load();}
  }

  //! Draw the Widget
  void draw() {
    int x = Widget::get_x();
    int y = Widget::get_y();
    int size = _text.size();
    // Fill up our buffers
    std::vector<glm::vec2> verts;
    std::vector<glm::vec2> uvs;
    for (unsigned int = 0; i < size; i++) {
      // Build the verts for our rectangle (2 triangles)
      // This only works for a single row of text
      glm::vec2 vertex_up_left = glm::vec2(x+i*size, y+size);
      glm::vec2 vertex_up_right = glm::vec2(x+i*size+size, y+size);
      glm::vec2 vertex_down_right = glm::vec2(x+i*size+size, y);
      glm::vec2 vertex_down_left = glm::vec2(x+i*size, y);

      // Add the vertices to our list, that will be passed to OpenGL
      verts.push_back(vertex_up_left);
      verts.push_back(vertex_down_left);
      verts.push_back(vertex_up_right);

      verts.push_back(vertex_down_right);
      verts.push_back(vertex_up_right);
      verts.push_back(vertex_down_left);

      // Determine the UV Coordinates
      char character = text[i];
      float uv_x = (character%16)/16.0f;
      float uv_y = (character/16)/16.0f;

      glm::vec2 uv_up_left = glm::vec2(uv_x, uv_y);
      glm::vec2 uv_up_right = glm::vec2(uv_x+1.0f/16.0f, uv_y);
      glm::vec2 uv_down_right = glm::vec2(uv_x+1.0f/16.0f, (uv_y + 1.0f/16.0f));
      glm::vec2 uv_down_left = glm::vec2(uv_x, (uv_y + 1.0f/16.0f));

      // Add the vertices to our list, that will be passed to OpenGL
      uvs.push_back(uv_up_left);
      uvs.push_back(uv_down_left);
      uvs.push_back(uv_up_right);

      uvs.push_back(uv_down_right);
      uvs.push_back(uv_up_right);
      uvs.push_back(uv_down_left);
    }

    // Copy the buffers to OpenGL
    glBindBuffer(GL_ARRAY_BUFFER, text_vboID);
    glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(glm::vec2), \
                &verts[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, text_uvID);
    glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(glm::vec2), \
                &uvs[0], GL_STATIC_DRAW);

    // Bind the shaders
    glUseProgram(text_shaderID);

    // Bind texture
    glActivateTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, text_textureID);

    // Set "myTextureSampler" sampler to suer Texture unit 0
    glUniformli(text_uniformID, 0);

    // Bind 1st buffer
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, text_vboID);
    glVertexAttribPointer(0, 2, GL_FLOAT, FL_FALSE, 0, (void*)0);

    // Bind the 2nd buffer
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, text_uvID);
    glVertexAttribPointer(1, 2, GL_FLOAT, FL_FALSE, 0, (void*)0);

    // Enable Blending and Alpha
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Draw the shape
    glDrawArrays(GL_TRIANGLES, 0, verts.size());

    // Cleanup
    glDisable(GL_BLEND);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    // Draw the children
    for (int i = 0; i < Widget::num_children(); i++) \
      {Widget::get_child(i)->draw();}
  }
};

}  // namespace Scui

#endif  // SRC_WIDGET_LABEL_H_
