#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

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
		std::cout << "Failed to create GLFW window" << std::endl;
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
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// Render loop to keep the program running
	while (!glfwWindowShouldClose(window))
	{
		// Swap the color buffer and show it as output to the window
		glfwSwapBuffers(window);
		// Check if any events are triggered and updates the window state
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