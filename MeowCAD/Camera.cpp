#include "Camera.h"
#include <iostream>


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
    // https://www.gamedev.net/forums/topic/666225-equation-for-zooming/
    // You want an exponential interpolation. An easy way to achieve that is to linearly interpolate in logarithmic domain.
    // Calculate the logarithm of your two end points : logMinZoom = log(minZoom) and logMaxZoom = log(maxZoom).
    // Linearly interpolate between logMinZoom and logMaxZoom in the desired number of steps : logZoom = logMinZoom + (logMaxZoom - logMinZoom) * step / (maxSteps - 1).
    // Transform logarithmic zoom to linear zoom : zoom = exp(logZoom).
    // This ensures that zoom increases or decreases with a uniform scale instead of with a uniform offset.
    
    //static double step = 1; // in Camera.h
    step += value;

    if (step < 0.1)
        step = 0.1;
    if (step > 100)
        step = 100;

    double maxSteps = 100;

    double minZoom = 0.1;
    double maxZoom = 100;
    double logMinZoom = log(minZoom);
    double logMaxZoom = log(maxZoom);
    double logZoom = logMinZoom + (logMaxZoom - logMinZoom) * step / (maxSteps - 1);
    cameraArmLength = exp(logZoom);

    std::cout << "step: " << step << std::endl;
    std::cout << "arm length: " << cameraArmLength << std::endl;
    
    //cameraArmLength += value;
    //if (cameraArmLength < 1)
    //    cameraArmLength = 1;
}

void Camera::focus(glm::vec3 focusPoint){
    cameraPos = focusPoint;
    //cameraArmLength = 10;
    // instead of reset arm length, we reset the step 
    step = 45;
    zoom(0);
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
