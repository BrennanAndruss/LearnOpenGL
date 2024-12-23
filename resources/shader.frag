#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;	// The texture at the texture unit 0
uniform sampler2D texture2;	// The texture at the texture unit 1
uniform float mixVal;

void main()
{
	FragColor = mix(texture(texture1, TexCoord), 
		texture(texture2, vec2(TexCoord.x * -1, TexCoord.y)), mixVal);
}