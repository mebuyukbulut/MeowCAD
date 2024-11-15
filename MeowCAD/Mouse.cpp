#include "Mouse.h"

/// <summary>
/// Calculate delta position of mouse cursor
/// </summary>
/// <param name="xposIn">New mouse position in horizontal direction</param>
/// <param name="yposIn">New mouse position in vertical direction</param>
void Mouse::update() {
    if (firstMouse) {
        lastPos = position;
        firstMouse = false;
    }

    offset.x = position.x - lastPos.x;
    offset.y = lastPos.y - position.y; // reversed since y-coordinates go from bottom to top
    
    lastPos = position;
}

void Mouse::reset() {
    firstMouse = true;
}

glm::vec2 Mouse::get_offset() {
    return offset;
}
void Mouse::reset_offset() {
    offset = glm::vec2(0.0f);
}


void Mouse::set_position(glm::vec2 newPosition){
    position = newPosition;
}
void Mouse::set_position(float x, float y){
    position = glm::vec2(x,y);
}

glm::vec2 Mouse::get_position(){
    return position;
}
