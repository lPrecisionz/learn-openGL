#version 330 core

in vec3 v_out_pos;
in vec3 v_out_color;
in vec2 v_out_tex_coord;

uniform sampler2D texture1;

out vec4 frag_color;

void main()
{
  frag_color = texture(texture1, v_out_tex_coord); 
};
