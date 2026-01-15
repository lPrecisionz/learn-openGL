#version 330 core

in vec3 our_color;
in vec3 out_pos;
in vec2 TexCoord;

out vec4 FragColor;
uniform sampler2D ourTexture_0;
uniform sampler2D ourTexture_1;

void main()
{
  FragColor = mix(texture(ourTexture_0, TexCoord), texture(ourTexture_1, vec2(TexCoord.x, TexCoord.y)), 0.2);
};
