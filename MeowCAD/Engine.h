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
//
//     SINGLETON PATTERN
//
    Engine() {}
public:
    static Engine& get(){
        static Engine instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return instance;
    }

    Engine(Engine const&) = delete;
    void operator=(Engine const&) = delete;


//
//     CLASS
//
private:
	glm::vec2 screen_resolution = glm::vec2(1200, 900);

    void my_config() {
        glPointSize(5);
        glEnable(GL_DEPTH_TEST);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        //glEnable(GL_FRAMEBUFFER_SRGB); // Gamma correction
        glEnable(GL_MULTISAMPLE); // MSAA - glfwWindowHint(GLFW_SAMPLES, 4);
    }

    void cleanup() {
        glfwTerminate();
    }

    void load_app_icon() {
        GLFWimage images[1];
        images[0].pixels = stbi_load("images/meow_icon.png", &images[0].width, &images[0].height, 0, 4); //rgba channels 
        glfwSetWindowIcon(window, 1, images);
        stbi_image_free(images[0].pixels);
    }

public:
    void exit() {
        glfwSetWindowShouldClose(window, true);
    }

	InputMode input_mode = InputMode::UI;

	Scene scene;
	Mouse mouse = Mouse(screen_resolution);

	GLFWwindow* window{};
	UI ui;

    EViewport viewport;



    void draw_background() {

    }

    void render_viewport() {


        if (viewport.is_dirty()) {
            auto res = viewport.get_resolution();
            //if (res.x != 0 || res.y != 0) {
                std::cout << res.x << "\t" << res.y << std::endl; 
                viewport.rescale_frame_buffer(res);
                viewport.set_dirty(false);
                scene.get_camera().update_screen_size(res.x, res.y);
            //}
        }

        viewport.bind();

        // draw cube map
        glDisable(GL_DEPTH_TEST);
        scene.draw_cubemap();

        // draw scene 
        glEnable(GL_DEPTH_TEST);
        scene.draw();
        viewport.unbind(screen_resolution.x, screen_resolution.y);

        
    }

    void render_loop(){
        
        while (!glfwWindowShouldClose(window)){
            processInput(window);

            if (viewport.is_active())
                render_viewport();

            glClearColor(0.1, 0.1, 0.1, 1.0);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            ui.render();

            // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }


    void main() {
        GlfwInitInfo glfw_init_info{
            screen_resolution.x,
            screen_resolution.y,
            "MeowCAD",
            //window
        };
        window = init::glfw(glfw_init_info);
        load_app_icon();

        init::glad();
        my_config();


        scene.get_camera().update_screen_size(screen_resolution.x, screen_resolution.y);

        Cube cube(0.3);
        Shape3D* shape = &cube;

        Texture texture;
        texture.init("images/image-1.jpg");

        Material material{};
        MaterialInfo material_info{};
        material_info.albedo = glm::vec3(0.39, 0.42, 0.18);
        material_info.metallic = 0.0f;
        material_info.roughness = 0.3f;
        material_info.ao = 0.1f;
        material.init(material_info,0, "material 1");


        Transform transform{};
        //transform.;

        //Mesh* my_mesh = new Mesh();
        //my_mesh->set_data(shape->get_data());
        //my_mesh->set_material(&material);
        //my_mesh->set_texture(&texture);
        //my_mesh->set_transform(transform);

        scene.init();
        //scene.add_mesh(my_mesh);

        for (int i = 0; i < 10; i++) {
            Mesh* new_mesh = new Mesh();
            new_mesh->set_ID(i); // Every mesh need a unique ID 
            new_mesh->set_name("mesh " + std::to_string(i));

            new_mesh->set_data(shape->get_data());
            new_mesh->set_material(&material);
            new_mesh->set_texture(&texture);
            transform.make_dirty();
            transform.set_position(glm::vec3(i, i, i));
            new_mesh->set_transform(transform);
            scene.add_mesh(new_mesh);
        }


        ui.init_UI(window);
        viewport.set(800, 600);
        ui.set_viewport(&viewport);
        render_loop();

        cleanup();
    }


    // process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
    void processInput(GLFWwindow* window) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        // tab mode 
        if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS) {
            input_mode = (input_mode == InputMode::GAME ? InputMode::UI : InputMode::GAME);
            glfwSetInputMode(window, GLFW_CURSOR, (input_mode == InputMode::GAME ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL));

            std::cout << "Input mode was changed" << std::endl;

            // disable UI
            ui.set_disabled(input_mode == InputMode::GAME);

            std::this_thread::sleep_for(std::chrono::milliseconds(300));
            mouse.reset();
        }

        if (input_mode == InputMode::UI)
            return;


        glm::vec3 delta_location{ 0,0,0 }; // x,y,z are dummy 
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) delta_location.x += 1;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) delta_location.x -= 1;

        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) delta_location.y -= 1;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) delta_location.y += 1;

        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) delta_location.z += 1;
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) delta_location.z -= 1;
        scene.get_camera().move(delta_location, scene.get_time().get_delta_time());
    }




};


