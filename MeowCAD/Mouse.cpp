#include "Mouse.h"

void Mouse::update(double xposIn, double yposIn) {
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    xoffset = xpos - lastX;
    yoffset = lastY - ypos; 
    // reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;
}

void Mouse::reset() {
    firstMouse = true;
}

glm::vec2 Mouse::get_offset() {
    return glm::vec2(xoffset, yoffset);
}
