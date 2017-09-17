#version 330 core

// Interpolated values from the vertex shaders
in vec2 uv;

// Ouput data
out vec4 col;

// Values that stay constant for the whole mesh.
uniform sampler2D myTextureSampler;

void main(){
  color = texture( myTextureSampler, uv );
}
