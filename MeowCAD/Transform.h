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
	glm::vec3 get_position() {
		return position;
	}
	glm::vec3 get_euler_rotation() {
		float x, y, z;
		auto eu = glm::eulerAngles(rotation);
		x = glm::degrees(eu.x);
		y = glm::degrees(eu.y);
		z = glm::degrees(eu.z);
		return glm::vec3(x, y, z);
	}
	glm::vec3 get_scale() {
		return scale;
	}
	void set_position(glm::vec3 position ) {
		make_dirty();
		this->position = position;
	}
	void set_euler_rotation(glm::vec3 rotation) {
		make_dirty();
		this->rotation = glm::quat(rotation);
	}
	void set_scale(glm::vec3 scale) {
		make_dirty();
		this-> scale = scale;
	}
	//void set_position(glm::vec3 position) {
	//	make_dirty();
	//	this->position = position;
	//}
	void move(glm::vec3 deltaPosition) {
		make_dirty();
		position += deltaPosition;
	}

	glm::mat4 get_model_matrix();	
	void make_dirty();
	

	//void set_transform(glm::vec3 eulerRotatio)
};


//    // quaternion
//    // https://www.opengl-tutorial.org/intermediate-tutorials/tutorial-17-quaternions/#how-do-i-create-a-quaternion-in-c-
//    // https://glm.g-truc.net/0.9.5/api/a00179.html
//    glm::quat myQuat(glm::vec3(0.f, 0.f, glfwGetTime()));
//    glm::quat myQuat2 = glm::angleAxis(static_cast<float>(glfwGetTime()), glm::vec3(0.f, 0.f, 1.f));
//    glm::mat4 RotationMatrix = glm::mat4_cast(myQuat);
