#pragma once

#include "USceneComponent.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
#include "shader.h"

class UCamera : public USceneComponent
{
private:
    double lastMouseX = 0.0;
    double lastMouseY = 0.0;

public:
    glm::mat4 camMat = glm::mat4(1.0f);;

    bool firstClick;
    int width, height;

    float speed = 5.0f;
    float sensitivity = 100.0f;

    UCamera(int width, int height, glm::vec3 position);

    void UpdateMatrix(float FOVdeg, float nearPlane, float farPlane);
    void Matrix(Shader& shader, const char* uniform);
    void Inputs(GLFWwindow* window, float deltaTime);
};
