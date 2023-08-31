#version 450

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 uv;

out vec3 g_color;

void main()
{
	gl_Position = vec4(position, 0);
	g_color = color;
}