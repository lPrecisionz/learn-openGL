#version 330 core
layout (location=0) in vec3 aPos;
layout (location=1) in vec3 aColor;

uniform float h_offset = 0;
out vec3 our_color;
out vec3 out_pos;

void main()
{
  our_color = aColor;
  gl_Position = vec4(aPos.x + h_offset, aPos.y, aPos.z, 1.0);
  out_pos = aPos;
};
