#include "Mesh.h"
#include "Data.h"
#include "Object.h"
#include "InstancedObject.h"
#include "FuncLib.h"
#include "WorldTimeHandler.h"

constexpr int width = 1600, height = 900;

glm::vec4 lightCol = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
glm::vec3 lightPos = glm::vec3(0.75f, 0.0f, 0.0f);
glm::vec3 grassPos = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 grassPos1 = glm::vec3(3.0f, 0.0f, 0.0f);
glm::vec3 swordPos = glm::vec3(1.0f, 0.0f, 0.0f);

int main() {
	// Initialize GLFW
	glfwInit();

	// Set GLFW versions
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 1);

	// Actually create the window
	GLFWwindow* window = glfwCreateWindow(width, height, "OpenGL_Proj1 Window", nullptr, nullptr);

	// Check if the window was created successfully
	if (window == NULL)
	{
		// Terminate if it failed to create the window
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Actually display the window
	glfwMakeContextCurrent(window);

	// Load OpenGL functions using GLAD
	gladLoadGL();

	// Set the viewport size and clear color
	glViewport(0, 0, width, height);

	InstancedObject grassField("Grass", "Grass");

	for (float i = 0; i < 14; i++)
	{
		for (float j = 0; j < 14; j++)
		{
			grassField.AddInstance(Transform{ glm::vec3(i, 0.0f, j), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f) });
		}
	}

	// Enables the depth buffer
	glEnable(GL_DEPTH_TEST);

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	WTH::UpdateTime();
	// Main loop to keep the window open
	while (!glfwWindowShouldClose(window))
	{	
		WTH::UpdateTime();
		// Set the clear color to a dark blue shade
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clear the color and the depth buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.Inputs(window, WTH::DeltaTimeSec());
		camera.UpdateMatrix(45.0f, 0.01f, 500.0f);

		grassField.DrawInstances(camera);

		// Swap the buffers to display the window
		glfwSwapBuffers(window);
		// Poll for events (like keyboard input, mouse movement, etc.)
		glfwPollEvents();
	}

	// Clean up and close the window

	glfwDestroyWindow(window); // Destroy the window
	glfwTerminate(); // Terminate GLFW
	return 0; 
}