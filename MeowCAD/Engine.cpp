#include "Engine.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    //Engine::get().scene.get_camera().update_screen_size(width, height);
}
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
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
