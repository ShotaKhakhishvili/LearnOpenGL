#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <chrono>
#include "shader.h"
#include "texture.h"
#include "VAO.h"
#include "Camera.h"
#include "WorldTimeHandler.h"

GLfloat vertices[] =
{
	//---------------------COORDS---------------------//	//---COLORS----//	  //--Tex Coords--//
	-0.5f,			-0.5f,		0.0f,						0.0f, 1.0f, 0.0f,		0.024f,	0.353f,			// Lower Left
	-0.5f,			 0.5f,		0.0f,						1.0f, 1.0f, 0.0f,		0.262f,	0.353f,			// Upper left 
	 0.5f,			 0.5f ,		0.0f,						1.0f, 0.0f, 1.0f,		0.262f,	0.647f,			// Upper right
	 0.5f,			-0.5f,		0.0f,						0.0f, 1.0f, 1.0f,		0.024f,	0.647f,			// Lower right 

	-0.5f,			-0.5f,	   -0.5f,						0.0f, 1.0f, 0.0f,		0.024f,	0.353f,			// Lower Left
	-0.5f,			 0.5f,	   -0.5f,						1.0f, 1.0f, 0.0f,		0.262f,	0.353f,			// Upper left 
	 0.5f,			 0.5f ,	   -0.5f,						1.0f, 0.0f, 1.0f,		0.262f,	0.647f,			// Upper right
	 0.5f,			-0.5f,	   -0.5f,						0.0f, 1.0f, 1.0f,		0.024f,	0.647f,			// Lower right 
};

GLuint indices[] = {
	0, 2, 1,
	0, 3, 2,
	4, 6, 5,
	4, 7, 6,
	0, 5, 4,
	0, 1, 5,
	2, 5, 1,
	2, 6, 5,
	2, 7, 6,
	2, 3, 7,
	0, 4, 7,
	0, 7, 3
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
float moveSpeed = 0.001f;

constexpr int width = 1600, height = 900;

int main() {
	// Initialize GLFW
	glfwInit();

	// Set GLFW versions
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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

	Shader shaderProgram = Shader("default.vert", "default.frag");

	// Set the viewport size and clear color
	glViewport(0, 0, width, height);

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, sizeof(GLfloat) * 8, (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, sizeof(GLfloat) * 8, (void*)(3 * sizeof(GL_FLOAT)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, sizeof(GLfloat) * 8, (void*)(6 * sizeof(GL_FLOAT)));

	VAO1.UnBind();
	VBO1.UnBind();
	EBO1.UnBind();

	// Texture
	Texture tex_grassBlock("Grass.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	tex_grassBlock.TexUnit(shaderProgram, "tex0", 0);

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
		// Clear the collor and the depth buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.Inputs(window, WTH::DeltaTimeSec());
			
		shaderProgram.Activate();

		camera.Matrix(45.0f, 0.1f, 500.0f, shaderProgram, "camMat");

		glBindTexture(GL_TEXTURE_2D, tex_grassBlock.ID);
		VAO1.Bind();

		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(GLuint), GL_UNSIGNED_INT, 0);

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
	tex_grassBlock.Delete();
	glfwDestroyWindow(window); // Destroy the window
	glfwTerminate(); // Terminate GLFW
	return 0; 
}