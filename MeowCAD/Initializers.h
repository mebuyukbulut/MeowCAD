#pragma once
#include <iostream>

struct GLFWwindow;

struct GlfwInitInfo {
    unsigned int scr_width{};
    unsigned int scr_height{};
    const char* window_title{};
    GLFWwindow* window{};

};

namespace init {
    GLFWwindow* glfw(GlfwInitInfo& initInfo);
    
    
    void glad();
}



class Initializers
{
};

