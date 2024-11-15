#pragma once
#include <glm/gtc/type_ptr.hpp>

class Mouse{
    bool firstMouse{ true };
	float lastX{};
	float lastY{};

    float xoffset{};
    float yoffset{};

    glm::vec2 position;
public:
    Mouse(glm::vec2 screenResolution) {
        lastX = screenResolution.x / 2.0;
        lastY = screenResolution.y / 2.0;
    }

    void update();
    void reset();
    glm::vec2 get_offset();
    void reset_offset();


    void set_position(glm::vec2 newPosition);
    void set_position(float x, float y);

    glm::vec2 get_position();

};

