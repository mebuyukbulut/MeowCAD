#pragma once

#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "Vertex.h"

class ObjParser
{
	

	glm::vec3 positions;
	glm::vec3 normals;
	glm::vec2 texCoords;

	//void read_normals();
	//void read_positions();
	//void read_texture_coordinates();

	// read file
	// seperate lines
	// create list of positions by according the beginning of line
	// create list of normals by according the beginning of line
	// create list of texCoords by according the beginning of line
	// create list of face by according the beginning of line
	// create vertices from existed lists (Triangulation?)
	// 

};

