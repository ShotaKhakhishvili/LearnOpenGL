#include "Mesh.h"
#include "FuncLib.h"
#include "WorldTimeHandler.h"

Vertex vertices[] =
{
	//----------------COORDS----------------//		//---------Normals----------//		//-----Vertex Colors-----//	 //-------------Texture UVs-----------//
	Vertex{glm::vec3(-0.5f,	-0.5f,		0.5f),		glm::vec3( 0.0f, -1.0f,  0.0f),		glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.9761904761904762f,	0.346f)},	// Lower Left Front
	Vertex{glm::vec3( 0.5f,	-0.5f,		0.5f),		glm::vec3( 0.0f, -1.0f,  0.0f),		glm::vec3(0.0f, 1.0f, 1.0f), glm::vec2(0.7380952380952381f,	0.346f)},	// Lower Right Front 
	Vertex{glm::vec3(-0.5f,	-0.5f,	   -0.5f),		glm::vec3( 0.0f, -1.0f,  0.0f),		glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.9761904761904762f,	0.639f)},	// Lower Left Back
	Vertex{glm::vec3( 0.5f,	-0.5f,	   -0.5f),		glm::vec3( 0.0f, -1.0f,  0.0f),		glm::vec3(0.0f, 1.0f, 1.0f), glm::vec2(0.7380952380952381f,	0.639f)},	// Lower Right Back

	Vertex{glm::vec3(-0.5f,	 0.5f,		0.5f),		glm::vec3( 0.0f,  1.0f,  0.0f),		glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(0.2619047619047619f,	0.346f)},	// Upper Left Front
	Vertex{glm::vec3( 0.5f,	 0.5f,		0.5f),		glm::vec3( 0.0f,  1.0f,  0.0f),		glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(0.4950000000000000f,	0.346f)},	// Upper Right Front
	Vertex{glm::vec3(-0.5f,	 0.5f,	   -0.5f),		glm::vec3( 0.0f,  1.0f,  0.0f),		glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(0.2619047619047619f,	0.639f)},	// Upper Left Back
	Vertex{glm::vec3( 0.5f,	 0.5f,	   -0.5f),		glm::vec3( 0.0f,  1.0f,  0.0f),		glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(0.4950000000000000f,	0.639f)},	// Upper Right Back
	
	Vertex{glm::vec3(-0.5f,	-0.5f,		0.5f),		glm::vec3( 0.0f,  0.0f,  1.0f),		glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.2619047619047619f,	0.045f)},	// Lower Left Front
	Vertex{glm::vec3(-0.5f,	 0.5f,		0.5f),		glm::vec3( 0.0f,  0.0f,  1.0f),		glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(0.2619047619047619f,	0.346f)},	// Upper Left Front
	Vertex{glm::vec3( 0.5f,	 0.5f,		0.5f),		glm::vec3( 0.0f,  0.0f,  1.0f),		glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(0.4950000000000000f,	0.346f)},	// Upper Right Front
	Vertex{glm::vec3( 0.5f,	-0.5f,		0.5f),		glm::vec3( 0.0f,  0.0f,  1.0f),		glm::vec3(0.0f, 1.0f, 1.0f), glm::vec2(0.4950000000000000f,	0.045f)},	// Lower Right Front

	Vertex{glm::vec3(-0.5f,	-0.5f,	   -0.5f),		glm::vec3( 0.0f,  0.0f, -1.0f),		glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.2639047619047619f,	0.938f)},	// Lower Left Back
	Vertex{glm::vec3(-0.5f,	 0.5f,	   -0.5f),		glm::vec3( 0.0f,  0.0f, -1.0f),		glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(0.2639047619047619f,	0.639f)},	// Upper Left Back
	Vertex{glm::vec3( 0.5f,	 0.5f,	   -0.5f),		glm::vec3( 0.0f,  0.0f, -1.0f),		glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(0.4950000000000000f,	0.639f)},	// Upper Right Back
	Vertex{glm::vec3( 0.5f,	-0.5f,	   -0.5f),		glm::vec3( 0.0f,  0.0f, -1.0f),		glm::vec3(0.0f, 1.0f, 1.0f), glm::vec2(0.4950000000000000f,	0.938f)},	// Lower Right Back
	
	Vertex{glm::vec3( 0.5f,	 0.5f,		0.5f),		glm::vec3( 1.0f,  0.0f,  0.0f),		glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(0.4950000000000000f,	0.3453)},	// Upper Right Front 
	Vertex{glm::vec3( 0.5f,	-0.5f,		0.5f),		glm::vec3( 1.0f,  0.0f,  0.0f),		glm::vec3(0.0f, 1.0f, 1.0f), glm::vec2(0.7380952380952381f,	0.3453)},	// Lower Right Front
	Vertex{glm::vec3( 0.5f,	 0.5f,	   -0.5f),		glm::vec3( 1.0f,  0.0f,  0.0f),		glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(0.4950000000000000f,	0.639f)},	// Upper Right Back
	Vertex{glm::vec3( 0.5f,	-0.5f,	   -0.5f),		glm::vec3( 1.0f,  0.0f,  0.0f),		glm::vec3(0.0f, 1.0f, 1.0f), glm::vec2(0.7380952380952381f,	0.639f)},	// Lower Right Back

	Vertex{glm::vec3(-0.5f,	-0.5f,		0.5f),		glm::vec3(-1.0f,  0.0f,  0.0f),		glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0240000000000000f,	0.346f)},	// Lower Left Front
	Vertex{glm::vec3(-0.5f,	 0.5f,		0.5f),		glm::vec3(-1.0f,  0.0f,  0.0f),		glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(0.2639047619047619f,	0.346f)},	// Upper Left Front
	Vertex{glm::vec3(-0.5f,	-0.5f,	   -0.5f),		glm::vec3(-1.0f,  0.0f,  0.0f),		glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0240000000000000f,	0.639f)},	// Lower Left Back
	Vertex{glm::vec3(-0.5f,	 0.5f,	   -0.5f),		glm::vec3(-1.0f,  0.0f,  0.0f),		glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(0.2639047619047619f,	0.639f)}	// Upper Left Back
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

Vertex vertices1[] =
{ //     COORDINATES     //
	Vertex{glm::vec3(-0.1f, -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3( 0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3( 0.1f, -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3( 0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f,  0.1f,  0.1f)}
};

GLuint indices1[] =
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
glm::vec3 lightPos = glm::vec3(0.75f, 0.0f, 0.0f);
glm::vec3 grassPos = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 grassPos1 = glm::vec3(2.0f, 0.0f, 0.0f);

int main() {
	// Initialize GLFW
	glfwInit();

	// Set GLFW versions
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);

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
	Shader shaderProgram1 = Shader("default.vert", "default.frag");
	Shader lightShader = Shader("light.vert", "light.frag");

	// Set the viewport size and clear color
	glViewport(0, 0, width, height);

	// Meshes

	Texture textures[]
	{
		Texture ("Grass.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
		Texture ("Planks_Roughness.png", "specular", 1, GL_RED, GL_UNSIGNED_BYTE)
	};
	Texture texturesSphere[]
	{
		Texture("Planks_BaseColor.png", "diffuse", 0, GL_RGB, GL_UNSIGNED_BYTE),
		Texture("Planks_Roughness.png", "specular", 1, GL_RED, GL_UNSIGNED_BYTE)
	};
	std::vector<Vertex> grassVertices(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
	std::vector<GLuint> grassIndices(indices, indices + sizeof(indices) / sizeof(GLuint));
	std::vector<Texture> grassTextures(textures, textures + sizeof(textures) / sizeof(Texture));
	std::vector<Texture> sphereTextures(texturesSphere, texturesSphere + sizeof(texturesSphere) / sizeof(Texture));
	std::vector<Vertex> sphereVertices;
	std::vector<GLuint> sphereIndices;
	ReadFromObjIntoVectors("object.txt", sphereVertices, sphereIndices);
	Mesh grassMesh(grassVertices, grassIndices, grassTextures);
	Mesh grassMesh1(sphereVertices, sphereIndices, sphereTextures);


	std::cout << grassMesh1.indices.size() << "\n";

	std::vector<Vertex> lightVertices(vertices1, vertices1 + sizeof(vertices1) / sizeof(Vertex));
	std::vector<GLuint> lightIndices(indices1, indices1 + sizeof(indices1) / sizeof(GLuint));
	std::vector<Texture> lightTextures(textures, textures + sizeof(textures) / sizeof(Texture));
	Mesh lightMesh(lightVertices, lightIndices, lightTextures);

	// End Meshes
	glm::mat4 grassModel = glm::mat4(1.0f);
	grassModel = glm::translate(grassModel, grassPos);
	glm::mat4 grassModel1 = glm::mat4(1.0f);
	grassModel1 = glm::translate(grassModel1, grassPos1);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(grassModel));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightCol.x, lightCol.y, lightCol.z, lightCol.a);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	glUniform1f(glGetUniformLocation(shaderProgram.ID, "lightUse"), 1.0f);
	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightCol.x, lightCol.y, lightCol.z, lightCol.a);
	shaderProgram1.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram1.ID, "model"), 1, GL_FALSE, glm::value_ptr(grassModel1));
	glUniform4f(glGetUniformLocation(shaderProgram1.ID, "lightColor"), lightCol.x, lightCol.y, lightCol.z, lightCol.a);
	glUniform3f(glGetUniformLocation(shaderProgram1.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	glUniform1f(glGetUniformLocation(shaderProgram1.ID, "lightUse"), 1.0f);

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

		grassMesh.Draw(shaderProgram, camera);
		grassMesh1.Draw(shaderProgram1, camera);
		lightMesh.Draw(lightShader, camera);

		// Swap the buffers to display the window
		glfwSwapBuffers(window);
		// Poll for events (like keyboard input, mouse movement, etc.)
		glfwPollEvents();
	}

	// Clean up and close the window

	shaderProgram.Delete();
	lightShader.Delete();
	glfwDestroyWindow(window); // Destroy the window
	glfwTerminate(); // Terminate GLFW
	return 0; 
}