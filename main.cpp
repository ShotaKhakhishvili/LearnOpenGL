#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <chrono>
#include "shader.h"
#include "VAO.h"

GLfloat vertices[] =
{
	//---------------------COORDS---------------------//	//---COLORS----//
	-0.5f,			-0.5f * float(sqrt(3)) / 3,		0.0f,	1.0f, 0.0f, 0.0f,		// Lower left corner
	 0.5f,			-0.5f * float(sqrt(3)) / 3,		0.0f,	1.0f, 0.0f, 0.0f,		// Lower right corner
	 0.0f,			 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,	1.0f, 0.0f, 0.0f,		// Upper corner
	-0.5f / 2,		 0.5f * float(sqrt(3)) / 6,		0.0f,	0.0f, 0.0f, 1.0f,		// Inner left
	 0.5f / 2,		 0.5f * float(sqrt(3)) / 6,		0.0f,	0.0f, 0.0f, 1.0f,		// Inner right
	 0.0f,			-0.5f * float(sqrt(3)) / 3,		0.0f,	0.0f, 0.0f, 1.0f		// Inner down
};

GLuint indices[] = {
	0, 3, 5, // Lower left triangle
	3, 2, 4, // Upper triangle
	5, 4, 1  // Lower right triangle
};

template<typename T>
struct vec3
{
	T x, y, z;
	vec3()
	{}
	vec3(T xin, T yin, T zin)
		: x(xin), y(yin), z(zin)
	{}
};

vec3<GLfloat> offset = vec3<GLfloat>(0.0f, 0.0f, 0.0f);
bool moveDir = true;
long long last;

void moveOffset()
{
	auto now = std::chrono::system_clock::now();

	// Get duration since epoch in milliseconds
	long long nowms = std::chrono::duration_cast<std::chrono::milliseconds>(
		now.time_since_epoch()
	).count();

	GLfloat newVal;

	if (moveDir)
	{
		newVal = std::min(.5f, offset.x + ((float)(nowms - last)) / 500);
	}
	else
	{
		newVal = std::max(-.5f, offset.x - ((float)(nowms - last)) / 500);
	}

	if (newVal == 0.5f || newVal == -0.5f)moveDir = !moveDir;
	offset.x = newVal;
	last = nowms;
}

int main() {
	// Initialize GLFW
	glfwInit();

	// Set GLFW versions
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Actually create the window
	GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL_Proj1 Window", nullptr, nullptr);

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

	Shader shaderProgram = Shader("default.vert", "default.frag");

	// Set the viewport size and clear color
	glViewport(0, 0, 800, 800);

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, sizeof(GLfloat) * 6, (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, sizeof(GLfloat) * 6, (void*)(3 * sizeof(GL_FLOAT)));

	VAO1.UnBind();
	VBO1.UnBind();
	EBO1.UnBind();

	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "offset");

	std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();

	last = std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::system_clock::now().time_since_epoch()
	).count();


	// Main loop to keep the window open
	while (!glfwWindowShouldClose(window))
	{	
		// Set the clear color to a dark blue shade
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clear the collor buffer
		glClear(GL_COLOR_BUFFER_BIT);

		shaderProgram.Activate();
		moveOffset();
		glUniform3f(uniID, offset.x, offset.y, offset.z);
		VAO1.Bind();

		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		// Swap the buffers to display the window
		glfwSwapBuffers(window);

		// Poll for events (like keyboard input, mouse movement, etc.)
		glfwPollEvents();
	}

	// Clean up and close the window

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();
	glfwDestroyWindow(window); // Destroy the window
	glfwTerminate(); // Terminate GLFW
	return 0; 
}