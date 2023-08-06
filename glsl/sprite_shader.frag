#version 330 core
out vec4 FragColor;
  
in vec2 tex_coord;

uniform sampler2D my_texture;

void main()
{
    FragColor = texture(my_texture, tex_coord);
}