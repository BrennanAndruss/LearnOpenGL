#version 330 core
out vec4 FragColor;
// in vec3 ourColor;	// Input from vertex shader
in vec3 ourPos;			// Input from vertex shader

void main()
{
	// FragColor = vec4(ourColor, 1.0);
	FragColor = vec4(ourPos, 1.0);
}