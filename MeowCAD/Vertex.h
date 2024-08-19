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
};

