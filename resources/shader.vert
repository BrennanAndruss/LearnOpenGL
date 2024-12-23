#version 330 core
layout (location = 0) in vec3 aPos;			// Set position to attribute position 0
layout (location = 1) in vec3 aColor;		// Set color to attribute position 1
layout (location = 2) in vec2 aTexCoord;	// Set texture coordinates to attribute position 2

out vec3 ourColor;
out vec2 TexCoord;

void main()
{
	gl_Position = vec4(aPos, 1.0);
	ourColor = aColor;
	TexCoord = aTexCoord;
}