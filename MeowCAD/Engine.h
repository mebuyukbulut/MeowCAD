#pragma once
//#pragma execution_character_set("utf-8") // ?

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
//#define GLM_ENABLE_EXPERIMENTAL
//#include <glm/gtx/quaternion.hpp>

#include <chrono>
#include <thread>

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

#include "Camera.h"
#include "Mouse.h"
#include "Scene.h"

#include "Texture.h"
#include "Shader.h"
#include "VAO.h"
#include "VBO.h"
#include "Vertex.h"
#include "Material.h"
#include "MaterialManager.h"
#include "EViewport.h"

#include "Initializers.h"
#include "UI.h"
#include "ETime.h"

#include "Shape3D.h"
#include "Cube.h"


enum class InputMode{
    GAME,UI
};

class Engine{
// ----------------------------------------------------
//     SINGLETON PATTERN
// ----------------------------------------------------
public:
    static Engine& get(){
        static Engine instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return instance;
    }

    Engine(Engine const&) = delete;
    void operator=(Engine const&) = delete;
private:
    Engine() = default;



// ----------------------------------------------------
//     CLASS
// ----------------------------------------------------
public:
	InputMode input_mode = InputMode::UI;
	Scene scene;
	GLFWwindow* window{};
    EViewport viewport;
	UI ui;

    Mouse mouse = Mouse(screen_resolution);    

    void init();
    void render_viewport();
    void render_loop();

    void set_screen_resolution(glm::vec2 newResolution);
    glm::vec2 get_screen_resolution();

    unsigned char* read_pixel_at_cursor();

    void exit();

private:
    glm::vec2 screen_resolution = glm::vec2(1200, 900);

    void load_app_icon();
    void my_config();
    void cleanup();
    void processInput(GLFWwindow* window);

};


