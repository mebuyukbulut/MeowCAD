#include "Engine.h"
//#pragma execution_character_set("utf-8") // ?

#include <chrono>
#include <thread>

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
//#define GLM_ENABLE_EXPERIMENTAL
//#include <glm/gtx/quaternion.hpp>

#include "LogUtils.h"

#include "Camera.h"

#include "Texture.h"
#include "Shader.h"
#include "VAO.h"
#include "VBO.h"
#include "Vertex.h"
#include "Material.h"
#include "MaterialManager.h"

#include "Initializers.h"
#include "ETime.h"

#include "Shape3D.h"
#include "Cube.h"
#include "Mesh.h"



// ----------------------------------------------------
// GLFW CALLBACKS
// ----------------------------------------------------

/// <summary>
/// This function was called when size of the main window was changed. 
/// </summary>
/// <param name="window">GLFWwindow pointer</param>
/// <param name="width">New width of the window</param>
/// <param name="height">New height of the window</param>
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    Engine::get().set_screen_resolution(glm::vec2(width,height));
}
/// <summary>
/// This function was called when mouse cursor move. It is update mouse and camera class according to InputMode
/// </summary>
/// <param name="window">GLFWwindow pointer</param>
/// <param name="xposIn">Horizontal mouse position on screen</param>
/// <param name="yposIn">Vertical mouse position on screen</param>
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
    Engine::get().mouse.set_position(xposIn, yposIn);

    if (Engine::get().input_mode == InputMode::UI)
        return;

    Engine::get().mouse.update();
}
/// <summary>
/// This fucntion was called when mouse scrool was moved.
/// "A normal mouse wheel, being vertical, provides offsets along the Y-axis."
/// </summary>
/// <param name="window">GLFWwindow pointer</param>
/// <param name="xoffset"></param>
/// <param name="yoffset">Scrool value</param>
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    if(Engine::get().viewport.is_hovered())
        Engine::get().scene.get_camera().zoom(yoffset);
}



// ----------------------------------------------------
// PUBLIC FUNCTIONS
// ----------------------------------------------------

/// <summary>
/// Read the final color of the pixel on the screen. It takes the position of mouse cursor from the Mouse class.
/// </summary>
/// <returns>Returns RGB values in a char array. 1 byte per color -> 3 byte total. Color values are between of 0 and 1 (?) </returns>
unsigned char* Engine::read_pixel_at_cursor() {
    int nWidth = 1;
    int nHeight = 1;
    unsigned char* pRGB = new unsigned char[3 * nWidth * nHeight];
    auto mos_pos = mouse.get_position();
    auto scr_res = get_screen_resolution();
    //std::cout << scr_res.y << std::endl;

    glReadPixels((int)mos_pos.x, (int)(scr_res.y - mos_pos.y),
        nWidth, nHeight,
        GL_RGB, GL_UNSIGNED_BYTE, pRGB);
    //std::cout << "("
    //    << (int)pRGB[0] << ", "
    //    << (int)pRGB[1] << ", "
    //    << (int)pRGB[2] << ", "
    //    << std::endl;
    return pRGB;
}

/// <summary>
/// Set screen resolution of entire application. 
/// </summary>
/// <param name="newResolution"></param>
void Engine::set_screen_resolution(glm::vec2 newResolution){
    screen_resolution = newResolution;
    // there are too much sequencer log for this 
    std::string message = 
        "New screen resolution: (" + std::to_string(screen_resolution.x)
        + ", " + std::to_string(screen_resolution.y) + ")";
    LogUtils::get().log(message);
}

/// <summary>
/// Get screen resolution of entire application 
/// </summary>
/// <returns></returns>
glm::vec2 Engine::get_screen_resolution(){
    return screen_resolution;
}

/// <summary>
/// Finish application
/// </summary>
void Engine::exit() {
    glfwSetWindowShouldClose(window, true);
}


void Engine::init() {
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



    Transform transform{};
    scene.init();
    //scene.add_mesh(my_mesh);

    for (int i = 0; i < 10; i++) {
        Mesh* new_mesh = new Mesh();
        new_mesh->set_ID(i); // Every mesh need a unique ID 
        new_mesh->set_name("mesh " + std::to_string(i));

        new_mesh->set_data(shape->get_data());


        auto material = MaterialManager::get().create_material();
        new_mesh->set_material(material);
        new_mesh->set_texture(&texture);
        transform.make_dirty();
        transform.set_position(glm::vec3(i, i, i));
        new_mesh->set_transform(transform);
        scene.mesh_manager.add_mesh(new_mesh);
    }


    ui.init_UI(window);
    viewport.set(800, 600);
    ui.set_viewport(&viewport);
    render_loop();

    cleanup();
}



// ----------------------------------------------------
// PRIVATE FUNCTIONS
// ----------------------------------------------------


void Engine::render_viewport() {

    if (viewport.is_dirty()) {
        auto res = viewport.get_resolution();
        //std::cout << res.x << "\t" << res.y << std::endl;
        viewport.rescale_frame_buffer(res);
        viewport.set_dirty(false);
        scene.get_camera().update_screen_size(res.x, res.y);
        
    }

    viewport.bind();

    // mesh selector 
    scene.mesh_selector.draw();
    //std::cout << 
    //    (int)read_pixel_at_cursor()[0] << 
    //    (int)read_pixel_at_cursor()[1] << 
    //    (int)read_pixel_at_cursor()[2] << std::endl;


    int pixel_at_loc = (int)read_pixel_at_cursor()[0];

    if (pixel_at_loc % 5 == 0 && pixel_at_loc != 205) {
        if(pixel_at_loc / 5)
            selected_mesh_index = pixel_at_loc / 5;

        //std::cout << pixel_at_loc << std::endl;
        //std::cout << selected_mesh_index << std::endl;
    }
    else
        selected_mesh_index = -1; 



    // draw cube map
    glDisable(GL_DEPTH_TEST);
    scene.skybox.draw();

    // draw scene 
    glClear(GL_DEPTH_BUFFER_BIT);   
    glEnable(GL_DEPTH_TEST);
    scene.draw();

    viewport.unbind(screen_resolution.x, screen_resolution.y);


}

void Engine::render_loop() {
    while (!glfwWindowShouldClose(window)) {

        processInput(window);         
        scene.get_time().update();

        if (viewport.is_active())
            render_viewport();

        //glClearColor(0.1, 0.1, 0.1, 1.0);
        glClear(GL_DEPTH_BUFFER_BIT);
        ui.render();

        mouse.reset_offset();

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}



void Engine::my_config() {
    glPointSize(5);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    //glEnable(GL_FRAMEBUFFER_SRGB); // Gamma correction
    glEnable(GL_MULTISAMPLE); // MSAA - glfwWindowHint(GLFW_SAMPLES, 4);
}

void Engine::cleanup() {
    glfwTerminate();
}


/// <summary>
/// Load MeowCAD window icon 
/// </summary>
void Engine::load_app_icon() {
    GLFWimage images[1];
    images[0].pixels = stbi_load("images/meow_icon.png", &images[0].width, &images[0].height, 0, 4); //rgba channels 
    glfwSetWindowIcon(window, 1, images);
    stbi_image_free(images[0].pixels);
}


/// <summary>
/// Process keyboard inputs. Set windows X close button, handle input mode and move camera 
/// </summary>
void Engine::processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) && input_mode == InputMode::UI) {
        int selected = Engine::get().selected_mesh_index;
        if ( selected != -1) {
            Engine::get().scene.mesh_manager.select_mesh(selected);
            //std::cout << selected << std::endl;
        }
        else if(viewport.is_hovered()){
            Engine::get().scene.mesh_manager.deselect_mesh();
        }

    }


    // tab mode 
    if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS && input_mode == InputMode::UI) {
        input_mode = InputMode::GAME;
        glfwSetInputMode(window, GLFW_CURSOR, (input_mode == InputMode::GAME ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL));

        std::cout << "InputMode::GAME" << std::endl;

        // disable UI
        ui.set_disabled(true);

        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        mouse.reset();
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_RELEASE && input_mode == InputMode::GAME) {
        
        input_mode = InputMode::UI;
        glfwSetInputMode(window, GLFW_CURSOR, (input_mode == InputMode::GAME ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL));

        std::cout << "InputMode::UI" << std::endl;

        // disable UI
        ui.set_disabled(false);

        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        mouse.reset();
    }

    if (glfwGetKey(window, GLFW_KEY_KP_DECIMAL) == GLFW_PRESS)
        if (Mesh* selected_mesh = scene.mesh_manager.get_selected_mesh()) {
            auto new_pos = selected_mesh->get_transform().get_position();
            scene.get_camera().focus(new_pos);
        }

    if (input_mode == InputMode::UI)
        return;

    // movement 
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        auto offset = mouse.get_offset();
        glm::vec3 delta_location{ 0, offset.x,offset.y }; // x,y,z are dummy 
        scene.get_camera().move(delta_location, scene.get_time().get_delta_time());
    }
    else {
        auto offset = mouse.get_offset();
        scene.get_camera().mouse(offset.x, offset.y);
    }




    
}
