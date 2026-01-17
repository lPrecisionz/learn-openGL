#version 330 core
layout (location=0) in vec3 v_pos;
layout (location=1) in vec3 v_color;
layout (location=2) in vec2 v_tex_coord;

out vec3 v_out_pos;
out vec3 v_out_color;
out vec2 v_out_tex_coord;

void main()
{
  gl_Position =vec4(v_pos.x , v_pos.y, v_pos.z, 1.0);
  v_out_pos       = v_pos;
  v_out_color     = v_color;
  v_out_tex_coord = v_tex_coord;
}
