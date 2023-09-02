#version 460
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 uv;

uniform mat4x4 u_world;

out vec3 g_color;

void main()
{
	gl_Position = u_world * vec4(position, 1);
	g_color = color;
}