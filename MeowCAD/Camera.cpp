#include "Camera.h"

void Camera::mouse(float xoffset, float yoffset) {
    //std::cout << "camfront:"<< "\t"
    //    << cameraFront.x << "\t"
    //    << cameraFront.y << "\t"
    //    << cameraFront.z << "\t"
    //    <<"\n";

    float sensitivity = 0.1f; // change this value to your liking
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);

    cameraUp = glm::normalize(glm::cross(cameraFront, glm::cross(worldUp, cameraFront)));
}

void Camera::zoom(float value) {
    fov -= (float)value;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 45.0f)
        fov = 45.0f;
}

void Camera::move(glm::vec3 deltaLocation, float deltaTime) {
    float cameraSpeed = static_cast<float>(5 * deltaTime);

    if (fabs(deltaLocation.x) > 0.1)
        cameraPos += deltaLocation.x * cameraSpeed * cameraFront;
    if (fabs(deltaLocation.y) > 0.1)
        cameraPos += deltaLocation.y * glm::normalize(glm::cross(cameraFront, worldUp)) * cameraSpeed;
    if (fabs(deltaLocation.z) > 0.1)
        cameraPos += deltaLocation.z * cameraSpeed * cameraUp;
}
void Camera::update_screen_size(glm::ivec2 resolution) {
    update_screen_size(resolution.x, resolution.y);
}
void Camera::update_screen_size(unsigned int width, unsigned int height) {
    SCR_WIDTH = width;
    SCR_HEIGHT = height;
}

glm::mat4 Camera::get_projection() {
    return glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
}

glm::mat4 Camera::get_view() {
    return glm::lookAt(cameraPos, cameraPos + cameraFront, worldUp);
}

glm::vec3 Camera::get_position() {
    return cameraPos;
}
