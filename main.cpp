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
	//---------------------COORDS----------------------//	//-Vert Colors-//		//---------Tex Coords--------//		//-----Normals-----//
	-0.5f,			-0.5f,		0.0f,						0.0f, 1.0f, 0.0f,		0.9761904761904762f,	0.346f,		 0.0f, -1.0f,  0.0f,	// Lower Left Front
	 0.5f,			-0.5f,		0.0f,						0.0f, 1.0f, 1.0f,		0.7380952380952381f,	0.346f,		 0.0f, -1.0f,  0.0f,	// Lower Right Front 
	-0.5f,			-0.5f,	   -1.0f,						0.0f, 1.0f, 0.0f,		0.9761904761904762f,	0.639f,		 0.0f, -1.0f,  0.0f,	// Lower Left Back
	 0.5f,			-0.5f,	   -1.0f,						0.0f, 1.0f, 1.0f,		0.7380952380952381f,	0.639f,		 0.0f, -1.0f,  0.0f,	// Lower Right Back
																														 			 	 
	-0.5f,			 0.5f,		0.0f,						1.0f, 1.0f, 0.0f,		0.2619047619047619f,	0.346f,		 0.0f,  1.0f,  0.0f,	// Upper Left Front
	 0.5f,			 0.5f ,		0.0f,						1.0f, 0.0f, 1.0f,		0.4950000000000000f,	0.346f,		 0.0f,  1.0f,  0.0f,	// Upper Right Front
	-0.5f,			 0.5f,	   -1.0f,						1.0f, 1.0f, 0.0f,		0.2619047619047619f,	0.639f,		 0.0f,  1.0f,  0.0f,	// Upper Left Back
	 0.5f,			 0.5f ,	   -1.0f,						1.0f, 0.0f, 1.0f,		0.4950000000000000f,	0.639f,		 0.0f,  1.0f,  0.0f,	// Upper Right Back
																														 
	-0.5f,			-0.5f,		0.0f,						0.0f, 1.0f, 0.0f,		0.2619047619047619f,	0.045f,		 0.0f,  0.0f,  1.0f,	// Lower Left Front
	-0.5f,			 0.5f,		0.0f,						1.0f, 1.0f, 0.0f,		0.2619047619047619f,	0.346f,		 0.0f,  0.0f,  1.0f,	// Upper Left Front
	 0.5f,			 0.5f ,		0.0f,						1.0f, 0.0f, 1.0f,		0.4950000000000000f,	0.346f,		 0.0f,  0.0f,  1.0f,	// Upper Right Front
	 0.5f,			-0.5f,		0.0f,						0.0f, 1.0f, 1.0f,		0.4950000000000000f,	0.045f,		 0.0f,  0.0f,  1.0f,	// Lower Right Front
																														 
	-0.5f,			-0.5f,	   -1.0f,						0.0f, 1.0f, 0.0f,		0.2639047619047619f,	0.938f,		 0.0f,  0.0f, -1.0f,	// Lower Left Back
	-0.5f,			 0.5f,	   -1.0f,						1.0f, 1.0f, 0.0f,		0.2639047619047619f,	0.639f,		 0.0f,  0.0f, -1.0f,	// Upper Left Back
	 0.5f,			 0.5f ,	   -1.0f,						1.0f, 0.0f, 1.0f,		0.4950000000000000f,	0.639f,		 0.0f,  0.0f, -1.0f,	// Upper Right Back
	 0.5f,			-0.5f,	   -1.0f,						0.0f, 1.0f, 1.0f,		0.4950000000000000f,	0.938f,		 0.0f,  0.0f, -1.0f,	// Lower Right Back
																														 			  
	 0.5f,			 0.5f ,		0.0f,						1.0f, 0.0f, 1.0f,		0.4950000000000000f,	0.3453f,	 1.0f,  0.0f,  0.0f,	// Upper Right Front 
	 0.5f,			-0.5f,		0.0f,						0.0f, 1.0f, 1.0f,		0.7380952380952381f,	0.3453f,	 1.0f,  0.0f,  0.0f,	// Lower Right Front
	 0.5f,			 0.5f ,	   -1.0f,						1.0f, 0.0f, 1.0f,		0.4950000000000000f,	0.639f,		 1.0f,  0.0f,  0.0f,	// Upper Right Back
	 0.5f,			-0.5f,	   -1.0f,						0.0f, 1.0f, 1.0f,		0.7380952380952381f,	0.639f,		 1.0f,  0.0f,  0.0f,	// Lower Right Back
																																  
	-0.5f,			-0.5f,		0.0f,						0.0f, 1.0f, 0.0f,		0.0240000000000000f,	0.346f,	    -1.0f,  0.0f,  0.0f,	// Lower Left Front
	-0.5f,			 0.5f,		0.0f,						1.0f, 1.0f, 0.0f,		0.2639047619047619f,	0.346f,	    -1.0f,  0.0f,  0.0f,	// Upper Left Front
	-0.5f,			-0.5f,	   -1.0f,						0.0f, 1.0f, 0.0f,		0.0240000000000000f,	0.639f,	    -1.0f,  0.0f,  0.0f,	// Lower Left Back
	-0.5f,			 0.5f,	   -1.0f,						1.0f, 1.0f, 0.0f,		0.2639047619047619f,	0.639f,	    -1.0f,  0.0f,  0.0f,	// Upper Left Back
};

GLuint indices[] =
{
	0, 1, 2,
	3, 1, 2,
	4, 5, 6,
	7, 5, 6,
	8, 9, 10,
	8, 10, 11,
	12, 13, 14,
	12, 14, 15,
	16, 17, 18,
	19, 17, 18,
	20, 21, 22,
	23, 21, 22
};

GLfloat lightVertices[] =
{ //     COORDINATES     //
	-0.1f, -0.1f,  0.1f,
	-0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f,  0.1f,
	-0.1f,  0.1f,  0.1f,
	-0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f,  0.1f
};

GLuint lightIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};

constexpr int width = 1600, height = 900;
glm::vec4 lightCol = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
glm::vec3 lightPos = glm::vec3(0.0f, 2.0f, 0.0f);
glm::vec3 grassPos = glm::vec3(0.0f, -1.0f, 0.0f);

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
	Shader lightShader = Shader("light.vert", "light.frag");

	// Set the viewport size and clear color
	glViewport(0, 0, width, height);

	// Grass

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, sizeof(GLfloat) * 11, (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, sizeof(GLfloat) * 11, (void*)(3 * sizeof(GL_FLOAT)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, sizeof(GLfloat) * 11, (void*)(6 * sizeof(GL_FLOAT)));
	VAO1.LinkAttrib(VBO1, 3, 3, GL_FLOAT, sizeof(GLfloat) * 11, (void*)(8 * sizeof(GL_FLOAT)));

	VAO1.UnBind();
	VBO1.UnBind();
	EBO1.UnBind();

	glm::mat4 grassModel = glm::mat4(1.0f);
	grassModel = glm::translate(grassModel, grassPos);

	// Texture
	Texture tex_grassBlock("Grass.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	tex_grassBlock.TexUnit(shaderProgram, "tex0", 0);

	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(grassModel));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightCol.x, lightCol.y, lightCol.z, lightCol.a);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

	// Grass End

	// Light Cube

	VAO VAO2;
	VAO2.Bind();

	VBO VBO2(lightVertices, sizeof(lightVertices));
	EBO EBO2(lightIndices, sizeof(lightIndices));

	VAO2.LinkAttrib(VBO2, 0, 3, GL_FLOAT, sizeof(GLfloat) * 3, (void*)0);

	VAO2.UnBind();
	VBO2.UnBind();
	EBO2.UnBind();

	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightCol.x, lightCol.y, lightCol.z, lightCol.a);
	// Light Cube End

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
		camera.UpdateMatrix(45.0f, 0.1f, 500.0f);

		shaderProgram.Activate();
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		camera.Matrix(shaderProgram, "camMat");

		glBindTexture(GL_TEXTURE_2D, tex_grassBlock.ID);
		tex_grassBlock.Bind();
		VAO1.Bind();

		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(GLuint), GL_UNSIGNED_INT, 0);

		lightShader.Activate();
		camera.Matrix(lightShader, "camMat");
		VAO2.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);

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