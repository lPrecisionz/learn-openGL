#version 330 core

in vec3 v_out_pos;
in vec3 v_out_color;

out vec4 frag_color;

void main()
{
  frag_color = vec4(v_out_color, 1.0); // not sure if this swizzling is allowed
};
