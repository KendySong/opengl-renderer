#version 460
in vec3 g_color;
in vec2 g_uv;

uniform vec3 u_color;
uniform int u_type;
uniform sampler2D u_texture;

out vec4 o_pixelColor;

void main()
{ 
    switch (u_type)
    {
        case 0 :
            o_pixelColor = vec4(u_color, 1);
            break;

        case 1 :
            o_pixelColor = texture(u_texture, g_uv);
            break;

        case 2 :
            //custom
            break;
    }	
}