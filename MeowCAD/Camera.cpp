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
    cameraArmLength += value;
    if (cameraArmLength < 1)
        cameraArmLength = 1;
}

void Camera::focus(glm::vec3 focusPoint){
    cameraPos = focusPoint;
    cameraArmLength = 10;
}

void Camera::move(glm::vec3 deltaLocation, float deltaTime) {
    float speed = - prefs.camera_speed * deltaTime;

    if (fabs(deltaLocation.x) > 0.1)
        cameraPos += deltaLocation.x * speed * cameraFront;
    if (fabs(deltaLocation.y) > 0.1)
        cameraPos += deltaLocation.y * speed * glm::normalize(glm::cross(cameraFront, worldUp));
    if (fabs(deltaLocation.z) > 0.1)
        cameraPos += deltaLocation.z * speed * cameraUp;
}
void Camera::update_screen_size(glm::ivec2 resolution) {
    update_screen_size(resolution.x, resolution.y);
}
void Camera::update_screen_size(unsigned int width, unsigned int height) {
    SCR_WIDTH = width;
    SCR_HEIGHT = height;
}

glm::mat4 Camera::get_projection() {
    return glm::perspective(glm::radians(prefs.fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, prefs.clip_start, prefs.clip_end);
}

glm::mat4 Camera::get_view() {
    auto camPos = cameraPos - cameraFront * cameraArmLength;
    return glm::lookAt(camPos, camPos + cameraFront, worldUp);
}

glm::vec3 Camera::get_position() {
    return cameraPos - cameraFront * cameraArmLength;
    //return cameraPos;
}
