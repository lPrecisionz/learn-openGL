#version 330 core
layout (location=0) in vec3 v_pos;
//layout (location=1) in vec3 v_color;
layout (location=1) in vec2 v_tex_coord;

out vec3 v_out_pos;
//out vec3 v_out_color;
out vec2 v_out_tex_coord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
  gl_Position = projection * view * model * vec4(v_pos, 1.0);
  v_out_pos       = v_pos;
  //v_out_color     = v_color;
  v_out_tex_coord = v_tex_coord;
}
