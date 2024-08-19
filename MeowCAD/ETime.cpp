#include "ETime.h"
#include <GLFW/glfw3.h>

void ETime::update() {
    current_time = glfwGetTime();
    delta_time = current_time - last_time;
    last_time = current_time;
}

double ETime::get_delta_time() {
    return delta_time;
}

