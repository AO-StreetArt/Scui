#version 330 core

// Input vertex data
layout(location = 0) in vec2 vertexPosition_screenspace;
layout(location = 1) in vec2 vertexUV;

// Output data
out vec2 uv;

void main(){
  // Output position of the vertex, in clip space
  // [0..800][0..600] -> [-400..400][-300..300]
  vec2 vertexPosition_homoneneousspace = vertexPosition_screenspace - vec2(400,300);
  vertexPosition_homoneneousspace /= vec2(400,300);
  gl_Position =  vec4(vertexPosition_homoneneousspace,0,1);

  // UV of the vertex.
  uv = vertexUV;
}
