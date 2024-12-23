#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include "shader.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SRC_WIDTH = 800;
const unsigned int SRC_HEIGHT = 600;

float mixVal = 0.2f;

int main()
{
	// Initialize GLFW
	glfwInit();
	// Configure GLFW to use OpenGL version 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Configure GLFW to use the core profile (no backwards compatibility)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a window object
	GLFWwindow* window = glfwCreateWindow(SRC_WIDTH, SRC_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == nullptr)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Make the context of our window the main context on the current thread
	glfwMakeContextCurrent(window);
	// Initialize the resize callback for the OpenGL viewport
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Initialize GLAD to manage function pointers for OpenGL
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// Build and compile our shader program
	Shader ourShader("../resources/shader.vert", "../resources/shader.frag");

	// Define vertex data for a rectangle shape
	float vertices[] = {
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   2.0f, 2.0f,   // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   2.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 2.0f    // top left 
	};
	// Define triangle indices for a rectangle shape
	unsigned int indices[] = {
		0, 1, 3,	// first triangle
		1, 2, 3		// second triangle
	};

	// Create and configure textures
	unsigned int texture1, texture2;
	glGenTextures(1, &texture1);
	glGenTextures(1, &texture2);

	// Flip textures vertically when loading them in
	stbi_set_flip_vertically_on_load(true);

	// Activate texture units and bind the first texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);

	// Set texture wrapping options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// Obtain the width, height, and number of color channels of the image
	int width, height, nrChannels;
	unsigned char* data = stbi_load("../resources/container.jpg", &width, &height, &nrChannels, 0);
	
	if (data)
	{
		// Generate the texture using the loaded image data
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		// Generate the mipmap levels for the texture
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cerr << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	// Configure the second texture
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);
	// Default texture wrap behavior is repeat
	data = stbi_load("../resources/awesomeface.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		// Specify that the image data contains an alpha channel for PNG images
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cerr << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	// Create and configure the vertex buffer object and vertex array object
	unsigned int VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Bind the vertex array object to store vertex attribute calls
	glBindVertexArray(VAO);

	// Copy vertex attributes into a vertex buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Copy indices into an element buffer for OpenGL to use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Set the vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	// Draw in wireframe mode

	// Render loop to keep the program running
	while (!glfwWindowShouldClose(window))
	{
		// Process inputs
		processInput(window);

		// Clear the color buffer to the current color state
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Activate the shader and set uniforms for texture samplers and mix value
		ourShader.use();
		ourShader.setInt("texture1", 0);
		ourShader.setInt("texture2", 1);
		ourShader.setFloat("mixVal", mixVal);

		// Activate texture units and bind textures
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		// Render the triangle
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// Swap front and back buffers to update output to window
		glfwSwapBuffers(window);
		// Poll IO events and update the window state
		glfwPollEvents();
	}

	// Terminate GLFW and free all resources
	glfwTerminate();
	return 0;
}

// Whenever the window size changed this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// Tell OpenGL the size of the resized rendering window
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	// Close the window when the escape key is pressed
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	// Increase the mix value when the up arrow key is pressed
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		mixVal += 0.001f;
		if (mixVal >= 1.0f)
			mixVal = 1.0f;
	}

	// Decrease the mix value when the down arrow key is pressed
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		mixVal -= 0.001f;
		if (mixVal <= 0.0f)
			mixVal = 0.0f;
	}
}