#include "Shape3D.h"

#include <glm/gtc/type_ptr.hpp>

void Shape3D::generate(){
	Vertex v1, v2, v3;
	v1.set_position(glm::vec3(-0.5f, -0.5f, 0.0f));
	v2.set_position(glm::vec3( 0.5f, -0.5f, 0.0f));
	v3.set_position(glm::vec3( 0.0f,  0.5f, 0.0f));
	data.push_back(v1);
	data.push_back(v2);
	data.push_back(v3);
}
