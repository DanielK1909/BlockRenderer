#version 330 core
layout (location = 0) in vec3 ipos;
layout (location = 2) in vec2 itex_coord;

uniform mat4 sprite;
uniform mat4 view;

out vec2 tex_coord;

void main()
{
    gl_Position = view * sprite * vec4(ipos, 1.0);
    tex_coord = itex_coord;
}