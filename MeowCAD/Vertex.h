#pragma once

#include <glm/glm.hpp>
#include <vector>

struct Vertex{
//public:
	float position[3]{};
	float normal[3]{};
	float color[4]{};
	float tex_coord[2]{};

	std::vector<float> get() {
		return {
			position[0],
			position[1],
			position[2],

			normal[0],
			normal[1],
			normal[2],

			color[0],
			color[1],
			color[2],
			color[3],

			tex_coord[0],
			tex_coord[1],
		};
	}

	void set_position(glm::vec3 position);
	void set_normal(glm::vec3 normal);
	void set_color(glm::vec4 color);
	void set_tex_coord(glm::vec2 tex_coord);


	glm::vec3 get_position();
	glm::vec3 get_normal();
	glm::vec4 get_color();
	glm::vec2 get_tex_coord();



};	