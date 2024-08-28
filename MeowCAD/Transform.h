#pragma once

#include <glm/gtc/type_ptr.hpp>

class Transform{
	glm::vec3 position{ 0.0f, 0.0f, 0.0f };
	glm::quat rotation{ 1.0f, 0.0f, 0.0f, 0.0f };
	glm::vec3 scale{ 1.0f, 1.0f, 1.0f };

	glm::mat4 modelMatrix = glm::mat4(1.0f);
	bool dirty{};

	glm::mat4 calculate_model_matrix();
public:
	glm::mat4 get_model_matrix();	
	void make_dirty();
	
	void set_position(glm::vec3 position) {
		this->position = position;
	}
	void move(glm::vec3 deltaPosition) {
		position += deltaPosition;
	}

	//void set_transform(glm::vec3 eulerRotatio)
};


//    // quaternion
//    // https://www.opengl-tutorial.org/intermediate-tutorials/tutorial-17-quaternions/#how-do-i-create-a-quaternion-in-c-
//    // https://glm.g-truc.net/0.9.5/api/a00179.html
//    glm::quat myQuat(glm::vec3(0.f, 0.f, glfwGetTime()));
//    glm::quat myQuat2 = glm::angleAxis(static_cast<float>(glfwGetTime()), glm::vec3(0.f, 0.f, 1.f));
//    glm::mat4 RotationMatrix = glm::mat4_cast(myQuat);
