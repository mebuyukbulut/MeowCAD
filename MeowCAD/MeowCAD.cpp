#pragma execution_character_set("utf-8") // ?

#include <glad/glad.h>
#include <GLFW/glfw3.h>

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

#include "Texture.h"
#include "Shader.h"
#include "VAO.h"
#include "VBO.h"
#include "Vertex.h"
#include "Material.h"

#include "Initializers.h"
#include "UI.h"
#include "ETime.h"

// discreate GPU 
#include <windows.h>
extern "C" {
    _declspec(dllexport) DWORD NvOptimusEnablement = 1;
    _declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}


unsigned int SCR_WIDTH = 1200;
unsigned int SCR_HEIGHT = 900;
glm::vec2 screen_resolution(SCR_WIDTH, SCR_HEIGHT);


enum class InputMode{
    GAME,UI
};
InputMode input_mode = InputMode::UI;

Camera camera;
Mouse mouse(screen_resolution);

GLFWwindow* window{};
Shader shader;
VAO vao;
VBO vbo;

UI ui;
ETime e_time;

void processInput(GLFWwindow* window);

void transforms(Shader& shader) {
    // create transformations
    glm::mat4 model = glm::mat4(1.0f); 
    
    // quaternion
    // https://www.opengl-tutorial.org/intermediate-tutorials/tutorial-17-quaternions/#how-do-i-create-a-quaternion-in-c-
    // https://glm.g-truc.net/0.9.5/api/a00179.html
    glm::quat myQuat(glm::vec3(0.f, 0.f, glfwGetTime()));
    glm::quat myQuat2 = glm::angleAxis(static_cast<float>(glfwGetTime()), glm::vec3(0.f, 0.f, 1.f));
    glm::mat4 RotationMatrix = glm::mat4_cast(myQuat);

    // mat4 ModelMatrix = TranslationMatrix * RotationMatrix * ScaleMatrix;
    model = RotationMatrix;
    //model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));

    glm::mat4 projection = camera.get_projection();
    glm::mat4 view = camera.get_view();

    //ourShader.use();
    shader.set("model", model);
    shader.set("view", view);
    shader.set("projection", projection);

    shader.set("viewPos", camera.get_position());

}


void render_loop() {

    float my_time{};
    while (!glfwWindowShouldClose(window))    {
        e_time.update();
        my_time += e_time.get_delta_time();
        processInput(window);

        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); 
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // draw our first triangle        
        //shader.use();
        shader.set("time", my_time);
        transforms(shader);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        ui.render();



        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void cleanup() {
    glfwTerminate();
}


int main(){
    GlfwInitInfo glfw_init_info{ 
        SCR_WIDTH, 
        SCR_HEIGHT, 
        "MeowCAD", 
        //window
    };
    window = init::glfw(glfw_init_info);
    init::glad();

    camera.update_screen_size(SCR_WIDTH, SCR_HEIGHT);

    glEnable(GL_DEPTH_TEST);

    //shader.init("shaders/base.vert", "shaders/base.frag");
    shader.init("shaders/material.vert", "shaders/material.frag");
    shader.use();

    std::vector<Vertex> vertices = {
            // back face 
            {{-0.5f, -0.5f, -0.5f}, { 0.0f,  0.0f, -1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},
            {{ 0.5f, -0.5f, -0.5f}, { 0.0f,  0.0f, -1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},
            {{ 0.5f,  0.5f, -0.5f}, { 0.0f,  0.0f, -1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
            {{ 0.5f,  0.5f, -0.5f}, { 0.0f,  0.0f, -1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
            {{-0.5f,  0.5f, -0.5f}, { 0.0f,  0.0f, -1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},
            {{-0.5f, -0.5f, -0.5f}, { 0.0f,  0.0f, -1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},
            // front face           {},
            {{-0.5f, -0.5f,  0.5f}, { 0.0f,  0.0f,  1.0f}, {1.0f, 0.0f, 0.0f, 0.5f}, {0.0f, 0.0f}}, 
            {{ 0.5f, -0.5f,  0.5f}, { 0.0f,  0.0f,  1.0f}, {0.0f, 1.0f, 0.0f, 0.5f}, {1.0f, 0.0f}}, 
            {{ 0.5f,  0.5f,  0.5f}, { 0.0f,  0.0f,  1.0f}, {0.0f, 0.0f, 1.0f, 0.5f}, {1.0f, 1.0f}},
            {{ 0.5f,  0.5f,  0.5f}, { 0.0f,  0.0f,  1.0f}, {1.0f, 0.0f, 0.0f, 0.5f}, {1.0f, 1.0f}},
            {{-0.5f,  0.5f,  0.5f}, { 0.0f,  0.0f,  1.0f}, {0.0f, 1.0f, 0.0f, 0.5f}, {0.0f, 1.0f}}, 
            {{-0.5f, -0.5f,  0.5f}, { 0.0f,  0.0f,  1.0f}, {0.0f, 0.0f, 1.0f, 0.5f}, {0.0f, 0.0f}},
            //                      {},
            {{-0.5f,  0.5f,  0.5f}, {-1.0f,  0.0f,  0.0f}, {1.0f, 0.0f, 0.0f, 0.5f}, {1.0f, 0.0f}},
            {{-0.5f,  0.5f, -0.5f}, {-1.0f,  0.0f,  0.0f}, {0.0f, 1.0f, 0.0f, 0.5f}, {1.0f, 1.0f}},
            {{-0.5f, -0.5f, -0.5f}, {-1.0f,  0.0f,  0.0f}, {0.0f, 0.0f, 1.0f, 0.5f}, {0.0f, 1.0f}},
            {{-0.5f, -0.5f, -0.5f}, {-1.0f,  0.0f,  0.0f}, {1.0f, 0.0f, 0.0f, 0.5f}, {0.0f, 1.0f}},
            {{-0.5f, -0.5f,  0.5f}, {-1.0f,  0.0f,  0.0f}, {0.0f, 1.0f, 0.0f, 0.5f}, {0.0f, 0.0f}},
            {{-0.5f,  0.5f,  0.5f}, {-1.0f,  0.0f,  0.0f}, {0.0f, 0.0f, 1.0f, 0.5f}, {1.0f, 0.0f}},
            //                      {},
            {{ 0.5f,  0.5f,  0.5f}, { 1.0f,  0.0f,  0.0f}, {1.0f, 0.0f, 0.0f, 0.5f}, {1.0f, 0.0f}},
            {{ 0.5f,  0.5f, -0.5f}, { 1.0f,  0.0f,  0.0f}, {0.0f, 1.0f, 0.0f, 0.5f}, {1.0f, 1.0f}},
            {{ 0.5f, -0.5f, -0.5f}, { 1.0f,  0.0f,  0.0f}, {0.0f, 0.0f, 1.0f, 0.5f}, {0.0f, 1.0f}},
            {{ 0.5f, -0.5f, -0.5f}, { 1.0f,  0.0f,  0.0f}, {1.0f, 0.0f, 0.0f, 0.5f}, {0.0f, 1.0f}},
            {{ 0.5f, -0.5f,  0.5f}, { 1.0f,  0.0f,  0.0f}, {0.0f, 1.0f, 0.0f, 0.5f}, {0.0f, 0.0f}},
            {{ 0.5f,  0.5f,  0.5f}, { 1.0f,  0.0f,  0.0f}, {0.0f, 0.0f, 1.0f, 0.5f}, {1.0f, 0.0f}},
            //                      {},
            {{-0.5f, -0.5f, -0.5f}, { 0.0f, -1.0f,  0.0f}, {1.0f, 0.0f, 0.0f, 0.5f}, {0.0f, 1.0f}},
            {{ 0.5f, -0.5f, -0.5f}, { 0.0f, -1.0f,  0.0f}, {0.0f, 1.0f, 0.0f, 0.5f}, {1.0f, 1.0f}},
            {{ 0.5f, -0.5f,  0.5f}, { 0.0f, -1.0f,  0.0f}, {0.0f, 0.0f, 1.0f, 0.5f}, {1.0f, 0.0f}},
            {{ 0.5f, -0.5f,  0.5f}, { 0.0f, -1.0f,  0.0f}, {1.0f, 0.0f, 0.0f, 0.5f}, {1.0f, 0.0f}},
            {{-0.5f, -0.5f,  0.5f}, { 0.0f, -1.0f,  0.0f}, {0.0f, 1.0f, 0.0f, 0.5f}, {0.0f, 0.0f}},
            {{-0.5f, -0.5f, -0.5f}, { 0.0f, -1.0f,  0.0f}, {0.0f, 0.0f, 1.0f, 0.5f}, {0.0f, 1.0f}},
            //                      {},
            {{-0.5f,  0.5f, -0.5f}, { 0.0f,  1.0f,  0.0f}, {1.0f, 0.0f, 0.0f, 0.5f}, {0.0f, 1.0f}},
            {{ 0.5f,  0.5f, -0.5f}, { 0.0f,  1.0f,  0.0f}, {0.0f, 1.0f, 0.0f, 0.5f}, {1.0f, 1.0f}},
            {{ 0.5f,  0.5f,  0.5f}, { 0.0f,  1.0f,  0.0f}, {0.0f, 0.0f, 1.0f, 0.5f}, {1.0f, 0.0f}},
            {{ 0.5f,  0.5f,  0.5f}, { 0.0f,  1.0f,  0.0f}, {1.0f, 0.0f, 0.0f, 0.5f}, {1.0f, 0.0f}},
            {{-0.5f,  0.5f,  0.5f}, { 0.0f,  1.0f,  0.0f}, {0.0f, 1.0f, 0.0f, 0.5f}, {0.0f, 0.0f}},
            {{-0.5f,  0.5f, -0.5f}, { 0.0f,  1.0f,  0.0f}, {0.0f, 0.0f, 1.0f, 0.5f}, {0.0f, 1.0f}},
    };


    vao.init();
    vbo.init();
    vbo.bind_data(vertices);

    Texture texture;
    texture.init("images/image-1.jpg");




    Material material;
    MaterialInfo material_info{};
    material_info.ambient = glm::vec3(1.0f, 0.5f, 0.31f);
    material_info.diffuse = glm::vec3(1.0f, 0.5f, 0.31f);
    material_info.specular = glm::vec3(0.5f, 0.5f, 0.5f);
    material_info.shininess = 32.0f;

    material.init(material_info, &shader);
    material.use();


    // lighting
    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

    shader.set("light.position", lightPos);
    shader.set("light.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
    shader.set("light.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
    shader.set("light.specular;", glm::vec3(1.0f, 1.0f, 1.0f));



    ui.init_UI(window);

    render_loop();

    cleanup();
    return 0;
}



// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow* window){
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // tab mode 
    if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS) {
        input_mode = (input_mode == InputMode::GAME ? InputMode::UI : InputMode::GAME);
        glfwSetInputMode(window, GLFW_CURSOR, (input_mode == InputMode::GAME ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL));

        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        mouse.reset();
    }

    if (input_mode == InputMode::UI)
        return;

    
    glm::vec3 delta_location{0,0,0}; // x,y,z are dummy 
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) delta_location.x += 1;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) delta_location.x -= 1;

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) delta_location.y -= 1;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) delta_location.y += 1;

    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) delta_location.z += 1;
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) delta_location.z -= 1;
    camera.move(delta_location, e_time.get_delta_time());
}




void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
    camera.update_screen_size(width, height);
}
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
    if (input_mode == InputMode::UI)
        return;

    mouse.update(xposIn, yposIn);

    auto offset = mouse.get_offset();
    camera.mouse(offset.x, offset.y);
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    camera.zoom(yoffset);
}


