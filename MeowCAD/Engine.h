#pragma once
#include <glm/gtc/type_ptr.hpp>
#include "Mouse.h"
#include "Scene.h"
#include "EViewport.h"
#include "UI.h"

struct GLFWwindow;


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

    void set_screen_resolution(glm::vec2 newResolution);
    glm::vec2 get_screen_resolution();

    unsigned char* read_pixel_at_cursor();

    void exit();

private:
    glm::vec2 screen_resolution = glm::vec2(1200, 900);

    void render_viewport();
    void render_loop();
    void load_app_icon();
    void my_config();
    void cleanup();
    void processInput(GLFWwindow* window);
};


