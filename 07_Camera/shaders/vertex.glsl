#version 330 core
layout (location=0) in vec3 aPos;
//layout (location=1) in vec3 aColor;
layout (location=1) in vec2 aTexCoord;

uniform float h_offset = 0;

uniform mat4  transform;
uniform mat4  model;
uniform mat4  view;
uniform mat4  projection;

out vec3 our_color;
out vec3 out_pos;
out vec2 TexCoord;

void main()
{
  //our_color = aColor;
  gl_Position = projection * view * model * vec4(aPos.x + h_offset, aPos.y, aPos.z, 1.0);
  out_pos = aPos;
  TexCoord = aTexCoord;
};
