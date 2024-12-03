#pragma once
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

struct CameraPreferences {
    float fov = 45.0f;
    float clip_start = 0.1f;
    float clip_end = 1000.f;
    float camera_speed = 1;
};

class Camera{
	// camera
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    float cameraArmLength = 10;
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	//glm::vec3 cameraRight = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);

	float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
	float pitch = 0.0f;

    CameraPreferences prefs{};

    unsigned int SCR_WIDTH{};
    unsigned int SCR_HEIGHT{};


    double step = 1;

public:

    void mouse(float xoffset, float yoffset);
    void zoom(float value);
    
    void focus(glm::vec3 focusPoint);
    void move(glm::vec3 deltaLocation, float deltaTime);
    void update_screen_size(glm::ivec2 resolution);
    void update_screen_size(unsigned int width, unsigned int height);

    glm::mat4 get_projection();
    glm::mat4 get_view();
    glm::vec3 get_position();

    CameraPreferences get_preference() {
        return prefs;
    }
    void set_preference(CameraPreferences prefs) {
        // we should add check for these prefs.

        if (prefs.clip_start < .1f)
            prefs.clip_start = .1f;

        if (prefs.clip_end < prefs.clip_start)
            prefs.clip_end = prefs.clip_start + .1;


        this->prefs = prefs;
    }

};

