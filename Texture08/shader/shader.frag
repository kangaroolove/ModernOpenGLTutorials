#version 330 core


out vec4 color;

in vec2 texCoord;
in vec3 ourColor;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	color = mix(texture(texture1, texCoord), texture(texture2, texCoord), 0.2);
}