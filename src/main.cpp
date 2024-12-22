#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SRC_WIDTH = 800;
const unsigned int SRC_HEIGHT = 600;

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
	
	// Define vertices in normalized device coordinates along with triangle indices
	float vertices[] = {
		// positions		// colors
		-0.5f, -0.5f, 0.0f,	1.0f, 0.0f, 0.0f,	// bottom left
		 0.5f, -0.5f, 0.0f,	0.0f, 1.0f, 0.0f,	// bottom right
		 0.0f,  0.5f, 0.0f,	0.0f, 0.0f, 1.0f	// top
	};

	// Create and configure the vertex buffer object and vertex array object
	unsigned int VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// Bind the vertex array object to store vertex attribute calls
	glBindVertexArray(VAO);

	// Copy vertex attributes into a vertex buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Set the vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	// Draw in wireframe mode

	// Render loop to keep the program running
	while (!glfwWindowShouldClose(window))
	{
		// Process inputs
		processInput(window);

		// Clear the color buffer to the current color state
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Activate the shader
		ourShader.use();

		// Set an offset for the triangle
		ourShader.setFloat("xOffset", 0.5f);

		// Render the triangle
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		// glBindVertexArray(0);

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
}