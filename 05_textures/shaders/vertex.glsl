#version 330 core
layout (location=0) in vec3 aPos;
layout (location=1) in vec3 aColor;
layout (location=2) in vec2 aTexCoord;

uniform float h_offset = 0;
out vec3 our_color;
out vec3 out_pos;
out vec2 TexCoord;
void main()
{
  our_color = aColor;
  gl_Position = vec4(aPos.x + h_offset, aPos.y, aPos.z, 1.0);
  out_pos = aPos;
  TexCoord = aTexCoord;
};
