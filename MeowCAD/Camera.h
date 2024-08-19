#pragma once
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
class Camera{
	// camera
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	//glm::vec3 cameraRight = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);

	float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
	float pitch = 0.0f;
	float fov = 45.0f;

    unsigned int SCR_WIDTH{};
    unsigned int SCR_HEIGHT{};

public:

    void mouse(float xoffset, float yoffset);
    void zoom(float value);
    
    void move(glm::vec3 deltaLocation, float deltaTime);
    void update_screen_size(unsigned int width, unsigned int height);

    glm::mat4 get_projection();
    glm::mat4 get_view();
    glm::vec3 get_position();


};

