#include "Mesh.h"
#include "Object.h"
#include "FuncLib.h"
#include "WorldTimeHandler.h"

constexpr int width = 1600, height = 900;

glm::vec4 lightCol = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
glm::vec3 lightPos = glm::vec3(0.75f, 0.0f, 0.0f);
glm::vec3 grassPos = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 grassPos1 = glm::vec3(3.0f, 0.0f, 0.0f);
glm::vec3 swordPos = glm::vec3(1.0f, 0.0f, 0.0f);

void initShaders()
{
	Object::MakeShader("SwordShader", "default.vert", "default.frag");
}

void init()
{
	initShaders();
}

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
	init();

	// Set the viewport size and clear color
	glViewport(0, 0, width, height);

	// Meshes

	std::shared_ptr<Texture> textures[]
	{
		std::make_shared<Texture>("Grass.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
		std::make_shared<Texture>("Planks_Roughness.png", "specular", 1, GL_RED, GL_UNSIGNED_BYTE)
	};
	std::shared_ptr<Texture> texturesSphere[]
	{
		std::make_shared<Texture>("Sword_BaseColor.png", "diffuse", 0, GL_RGB, GL_UNSIGNED_BYTE),
		std::make_shared<Texture>("Sword_Roughness.png", "specular", 1, GL_RED, GL_UNSIGNED_BYTE)
	};
	std::vector<TextureParameters> swordTextureParameters = 
	{
		TextureParameters{"Sword_BaseColor.png", "diffuse", 0, GL_RGB, GL_UNSIGNED_BYTE},
		TextureParameters{"Sword_Roughness.png", "specular", 1, GL_RED, GL_UNSIGNED_BYTE}
	};

	Shader shaderProgram = Shader("default.vert", "default.frag");
	Shader shaderProgram1 = Shader("default.vert", "default.frag");
	Shader lightShader = Shader("light.vert", "light.frag");

	std::vector<std::shared_ptr<Texture>> grassTextures(textures, textures + sizeof(textures) / sizeof(Texture));
	std::vector<std::shared_ptr<Texture>> sphereTextures(texturesSphere, texturesSphere + sizeof(texturesSphere) / sizeof(Texture));
	std::vector<std::shared_ptr<Texture>> lightTextures(textures, textures + sizeof(textures) / sizeof(Texture));

	std::vector<Vertex> grassVertices;
	std::vector<GLuint> grassIndices;
	ReadFromObjIntoVectors("Grass.txt", grassVertices, grassIndices);
	Mesh grassMesh(grassVertices, grassIndices, grassTextures);

	std::vector<Vertex> sphereVertices;
	std::vector<GLuint> sphereIndices;
	ReadFromObjIntoVectors("Sword.txt", sphereVertices, sphereIndices);
	Mesh grassMesh1(sphereVertices, sphereIndices, sphereTextures);

	std::vector<Vertex> lightVertices;
	std::vector<GLuint> lightIndices;
	ReadFromObjIntoVectors("Cube.txt", lightVertices, lightIndices);
	Mesh lightMesh(lightVertices, lightIndices, lightTextures);

	// End Meshes
	glm::mat4 grassModel = glm::mat4(1.0f);
	grassModel = glm::translate(grassModel, grassPos);
	glm::mat4 grassModel1 = glm::mat4(1.0f);
	grassModel1 = glm::translate(grassModel1, grassPos1);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);
	glm::mat4 swordModel = glm::mat4(1.0f);
	swordModel = glm::translate(swordModel, swordPos);

	Object sword("Sword.txt", "SwordShader", swordTextureParameters);
	std::shared_ptr<Shader> swordShader = sword.GetShader();
	swordShader->Activate();
	glUniform4f(glGetUniformLocation(swordShader->ID, "lightColor"), lightCol.x, lightCol.y, lightCol.z, lightCol.a);
	glUniform3f(glGetUniformLocation(swordShader->ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	glUniform1f(glGetUniformLocation(swordShader->ID, "lightUse"), 1.0f);

	shaderProgram.Activate();
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightCol.x, lightCol.y, lightCol.z, lightCol.a);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	glUniform1f(glGetUniformLocation(shaderProgram.ID, "lightUse"), 1.0f);
	lightShader.Activate();
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightCol.x, lightCol.y, lightCol.z, lightCol.a);
	shaderProgram1.Activate();
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

		//grassMesh.Draw(shaderProgram, camera);
		//grassMesh1.Draw(shaderProgram1, camera);
		lightMesh.Draw(lightShader, camera, lightModel);
		sword.Draw(camera);

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