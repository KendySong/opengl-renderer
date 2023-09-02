#version 460
in vec3 g_color;

uniform vec3 u_color;

out vec4 o_pixelColor;

void main()
{
	o_pixelColor = vec4(u_color, 1);
}