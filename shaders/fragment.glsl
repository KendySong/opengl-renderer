#version 460
in vec3 g_color;
in vec2 g_uv;

uniform vec3 u_color;
uniform sampler2D u_texture;

out vec4 o_pixelColor;

void main()
{ 
    //o_pixelColor = vec4(u_color, 1);
	o_pixelColor = texture(u_texture, g_uv);
}