#version 330 core
layout (location = 0) in vec3 aPos;			// Set position to attribute position 0
layout (location = 1) in vec2 aTexCoord;	// Set texture coordinates to attribute position 1

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	// Note: Matrix multiplication is read from right to left
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
	TexCoord = aTexCoord;
}