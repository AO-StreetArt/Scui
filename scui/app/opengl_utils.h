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

// Include GLEW
#include <GL/glew.h>

// Include OpenGL
#include <GL/gl.h>

// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Include SOIL
#include <SOIL/SOIL.h>

// Include other system libraries
#include <sys/stat.h>
#include <unordered_map>
#include <string>
#include <fstream>
#include <iostream>

#ifndef SRC_APP_OPENGL_UTILS_H_
#define SRC_APP_OPENGL_UTILS_H_

namespace Scui {

  //! OpenGlApp Exception

  //! A child class of std::exception
  //! which holds error information
  struct OpenGlAppException: public std::exception {
    // An error message passed on initialization
    std::string int_msg;
    const char * int_msg_cstr;

    // Create a Widget Exception, and store the given error message
    inline OpenGlAppException(std::string msg) {
      int_msg = "Error in OpenGL Application: " + msg;
      int_msg_cstr = int_msg.c_str();
    }

    OpenGlAppException() {}
    ~OpenGlAppException() throw() {}
    // Show the error message in readable format
    const char * what() const throw() {
      return int_msg_cstr;
    }
  };

  // Compile and check a single shader
  void compile_shader(const char * data, GLuint shaderID) {
    GLint result = GL_FALSE;
    int compile_log_len;

    // Compile the Shader
    std::cout << "Compiling Shader" << std::endl;
    glShaderSource(shaderID, 1, &data, NULL);
    glCompileShader(shaderID);

    // Check the Shader Compilation
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &compile_log_len);
    std::cout << "Shader Log Length: " << compile_log_len << std::endl;
    if (compile_log_len > 0) {
      GLchar *verr_log = new GLchar[compile_log_len];
      glGetShaderInfoLog(shaderID, compile_log_len, NULL, verr_log);
      if (result == GL_FALSE) {
        std::string verr_msg(verr_log);
        throw OpenGlAppException(verr_msg);
      } else {
        std::cout << verr_log << std::endl;
      }
      delete[] verr_log;
    }
  }

  // Read, compile, and link both a vertex and fragment shader
  GLuint compile_shaders(const char * vs_file, const char * frag_file) {
    // Create the shaders
    GLuint vertexID = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentID = glCreateShader(GL_FRAGMENT_SHADER);

    // String variable to store each line of the file
    std::string line;

    // String variables to store full program texts
    std::string full_vertex_text;
    std::string full_fragment_text;

    // Load the Vertex Shader
    struct stat buffer;
    if (stat(vs_file, &buffer) == 0) {
      std::ifstream vfile(vs_file);

      if (vfile.is_open()) {
        while (getline(vfile, line)) {
          full_vertex_text += "\n" + line;
        }
      }
    }

    // Load the Fragment Shader
    struct stat buf;
    if (stat(frag_file, &buf) == 0) {
      std::ifstream ffile(frag_file);

      if (ffile.is_open()) {
        while (getline(ffile, line)) {
          full_fragment_text += "\n" + line;
        }
      }
    }

    // Compile the shaders
    char const *vs_cstr = full_vertex_text.c_str();
    char const *fs_cstr = full_fragment_text.c_str();
    compile_shader(vs_cstr, vertexID);
    compile_shader(fs_cstr, fragmentID);

    // Link the shaders
    GLuint programID = glCreateProgram();
    glAttachShader(programID, vertexID);
    glAttachShader(programID, fragmentID);
    glLinkProgram(programID);

    // Check to ensure correct linkage
    GLint result = GL_FALSE;
    int compile_log_len;
    glGetProgramiv(programID, GL_LINK_STATUS, &result);
    glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &compile_log_len);
    if (compile_log_len > 0) {
      GLchar *lerr_log = new GLchar[compile_log_len];
      glGetProgramInfoLog(programID, compile_log_len, NULL, lerr_log);
      if (result == GL_FALSE) {
        std::string lerr_msg(lerr_log);
        throw OpenGlAppException(lerr_msg);
      } else {
        std::cout << lerr_log << std::endl;
      }
      delete[] lerr_log;
    }

    // Cleanup
    glDetachShader(programID, vertexID);
    glDetachShader(programID, fragmentID);
    glDeleteShader(vertexID);
    glDeleteShader(fragmentID);

    return programID;
  }

  // Load an image texture
  GLuint load_texture(const char * image_path) {
    // Load the image with SOIL
    int width, height;
    unsigned char* tex_image = SOIL_load_image(image_path, &width, &height, 0, SOIL_LOAD_RGB);

    // Create and bind the OpenGL Texture object
    GLuint texID;
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);

    // Assign the loaded image to the texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, tex_image);

    // Set up the texture to display a white color outisde the image boundaries
    float backg_color[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, backg_color);

    // Generate Mipmaps of the texture
    glGenerateMipmap(GL_TEXTURE_2D);

    // Free the memory used for our image
    SOIL_free_image_data(tex_image);

    return texID;
  }
}  // namespace Scui

#endif  // SRC_APP_OPENGL_UTILS_H_
