#include "Engine.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    Engine::get().set_screen_resolution(glm::vec2(width,height));
    //Engine::get().scene.get_camera().update_screen_size(width, height);
}
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
    Engine::get().set_mouse_position(xposIn, yposIn);

    if (Engine::get().input_mode == InputMode::UI)
        return;



    Engine::get().mouse.update(xposIn, yposIn);

    auto offset = Engine::get().mouse.get_offset();
    Engine::get().scene.get_camera().mouse(offset.x, offset.y);
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    if (Engine::get().input_mode == InputMode::UI)
        return;
    Engine::get().scene.get_camera().zoom(yoffset);
}

void Engine::set_screen_resolution(glm::vec2 newResolution){
    screen_resolution = newResolution;
}

glm::vec2 Engine::get_screen_resolution(){
    return screen_resolution;
}
