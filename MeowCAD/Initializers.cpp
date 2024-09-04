#include "Initializers.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);


namespace init {

    // initializer.h 
    void set_glfw_window_hints() {
        // glfw: initialize and configure
        // ------------------------------
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_SAMPLES, 4); // MSAA - glEnable(GL_MULTISAMPLE);
        glfwWindowHint(GLFW_MAXIMIZED, 1);

        //glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, 1); // it is not a neccessary feature 

#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    }
    GLFWwindow* create_glfw_window(GlfwInitInfo& initInfo) {
        GLFWwindow* window = glfwCreateWindow(initInfo.scr_width, initInfo.scr_height, initInfo.window_title, NULL, NULL);

        if (window == NULL) {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            exit(EXIT_FAILURE);
        }
        return window;
    }
    void init_glfw_callbacks(GlfwInitInfo& initInfo) {
        glfwSetFramebufferSizeCallback(initInfo.window, framebuffer_size_callback);
        glfwSetCursorPosCallback(initInfo.window, mouse_callback);
        glfwSetScrollCallback(initInfo.window, scroll_callback);
    }
    GLFWwindow* glfw(GlfwInitInfo& initInfo) {
        set_glfw_window_hints();
        initInfo.window = create_glfw_window(initInfo);
        glfwMakeContextCurrent(initInfo.window);
        glfwSwapInterval(1); // Enable vsync

        init_glfw_callbacks(initInfo);
        return initInfo.window;
    }



    void glad() { // glad: load all OpenGL function pointers
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            exit(EXIT_FAILURE);
        }
    }



}