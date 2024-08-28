#include "ETime.h"
#include <GLFW/glfw3.h>

void ETime::update() {
    // delta time
    current_time = glfwGetTime();
    delta_time = current_time - last_time;
    last_time = current_time;

    // elapsed time
    elapsed_time += delta_time;
}

double ETime::get_delta_time() {
    return delta_time;
}
double ETime::get_elapsed_time(){
    return elapsed_time;
}

