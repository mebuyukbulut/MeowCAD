#include "Mouse.h"

/// <summary>
/// Calculate delta position of mouse cursor
/// </summary>
/// <param name="xposIn">New mouse position in horizontal direction</param>
/// <param name="yposIn">New mouse position in vertical direction</param>
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
void Mouse::reset_offset() {
    xoffset = 0;
    yoffset = 0;
}

// why we use update and set_position ? 
// maybe we can combine this variables ? 
void Mouse::set_position(glm::vec2 newPosition){
    set_position(newPosition.x, newPosition.y);
}
void Mouse::set_position(float x, float y){
    position.x = x;
    position.y = y;
}

glm::vec2 Mouse::get_position(){
    return position;
}
