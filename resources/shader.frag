#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;	// The texture at the texture unit 0
uniform sampler2D texture2;	// The texture at the texture unit 1

void main()
{
	FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
}