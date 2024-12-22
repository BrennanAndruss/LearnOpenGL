#version 330 core
layout (location = 0) in vec3 aPos;		// Set position to attribute position 0
layout (location = 1) in vec3 aColor;	// Set color to attribute position 1

// out vec3 ourColor;	// Output color to fragment shader
out vec3 ourPos;			// Output positionto fragment shader

void main()
{
	gl_Position = vec4(aPos, 1.0);
	ourPos = aPos;
}