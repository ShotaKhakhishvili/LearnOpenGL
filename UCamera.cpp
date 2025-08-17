#include "UCamera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

UCamera::UCamera(int width, int height, glm::vec3 position)
    : USceneComponent(), width(width), height(height), firstClick(true)
{
    SetLocation(position); // uses USceneComponent transform system
}

void UCamera::UpdateMatrix(float FOVdeg, float nearPlane, float farPlane)
{
    // 1. Get world matrix from USceneComponent
    glm::mat4 worldMatrix = GetWorldMatrix();

    // 2. Invert to get view matrix
    glm::mat4 view = glm::inverse(worldMatrix);

    // 3. Projection matrix
    glm::mat4 proj = glm::perspective(
        glm::radians(FOVdeg),
        (float)width / (float)height,
        nearPlane,
        farPlane
    );

    // 4. Store final camera matrix (proj * view)
    camMat = proj * view;
}

void UCamera::Matrix(Shader& shader, const char* uniform)
{
    // Send camMat to shader
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform),
        1, GL_FALSE, glm::value_ptr(camMat));
}

void UCamera::Inputs(GLFWwindow* window, float deltaTime)
{
    const glm::vec3 worldUp(0, 1, 0); // Keep up vector constant
    float velocity = speed * deltaTime;

    // Get direction vectors from rotation quaternion
    glm::quat rotQuat = GetRotationInQuat();
    glm::vec3 forward = glm::normalize(rotQuat * glm::vec3(0, 0, -1));
    glm::vec3 right = glm::normalize(glm::cross(forward, worldUp));

    // Keyboard movement
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) OffsetLocation(forward * velocity);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) OffsetLocation(-forward * velocity);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) OffsetLocation(right * velocity);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) OffsetLocation(-right * velocity);
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) OffsetLocation(worldUp * velocity);
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) OffsetLocation(-worldUp * velocity);

    // Speed control
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) speed = 20.0f;
    else speed = 5.0f;

    // Mouse look
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

        if (firstClick)
        {
            glfwSetCursorPos(window, width / 2, height / 2);
            firstClick = false;
        }

        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);

        float rotX = sensitivity * static_cast<float>(mouseY - (height / 2)) / height;
        float rotY = sensitivity * static_cast<float>(mouseX - (width / 2)) / width;

        // Pitch rotation around right vector
        glm::quat pitchRot = glm::angleAxis(glm::radians(-rotX), right);

        // Limit pitch
        glm::vec3 newForward = glm::normalize((pitchRot * rotQuat) * glm::vec3(0, 0, -1));
        if (abs(glm::angle(newForward, worldUp) - glm::radians(90.0f)) <= glm::radians(85.0f))
        {
            rotQuat = pitchRot * rotQuat;
        }

        // Yaw rotation around constant world up
        glm::quat yawRot = glm::angleAxis(glm::radians(-rotY), worldUp);
        rotQuat = yawRot * rotQuat;

        SetRotationInQuat(rotQuat);

        glfwSetCursorPos(window, width / 2, height / 2);
    }
    else
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        firstClick = true;
    }
}
