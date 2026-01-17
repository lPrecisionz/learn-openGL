#version 330 core

in vec3 v_out_pos;
in vec3 v_out_color;

out vec4 frag_color;

void main()
{
  frag_color = v_out_color;
};
