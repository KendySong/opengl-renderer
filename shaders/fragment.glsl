#version 460
in vec3 g_color;
in vec2 g_uv;

uniform vec2 u_resolution;
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
            vec2 nCoord = gl_FragCoord.xy / u_resolution;
            o_pixelColor = vec4(sin(100 * (u_color.y / nCoord.x)), abs(cos(sin(nCoord.x/nCoord.y))), cos(100 * (u_color.y / nCoord.y)), 1);
            break;
    }	
}