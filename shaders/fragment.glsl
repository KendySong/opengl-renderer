#version 460
in vec3 g_color;

out vec4 o_pixelColor;

void main()
{
	o_pixelColor = vec4(g_color, 1);
}