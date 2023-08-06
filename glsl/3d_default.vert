#version 330 core
layout (location = 0) in vec3 ipos;
layout (location = 1) in vec2 itex_coord;
layout (location = 2) in vec3 inormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 colour;
out vec2 tex_coord;

void main()
{
    gl_Position = projection * view * model * vec4(ipos, 1.0);
    tex_coord = itex_coord;
}