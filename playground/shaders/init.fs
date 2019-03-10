#version 330 core

in vec3 color;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D sampler_tex;

void main()
{
    FragColor = texture(sampler_tex, TexCoord) * vec4(color, 1.0);
}