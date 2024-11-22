#pragma once

#include <iostream>
//#include <vector>
#include <map>

#include "Mesh.h"
#include "Transform.h"
#include "VAO.h"
#include "VBO.h"
#include "Vertex.h"
#include "IDGen.h"

class MeshManager{
	VAO vao;
	VBO vbo;
	IDGen idgen;

	int buffer_size{};
	int buffer_capacity{};
	int vertex_index{};

	std::map<uint32_t, std::string> mesh_names;

public:
	std::map<uint32_t, Mesh*> meshes;
	Mesh* selected_mesh{};
	std::map<uint32_t, Mesh*> selected_meshes;


	void init();

	void select_mesh(uint32_t ID);
	void deselect_mesh();
	void add_mesh(Mesh* mesh);

	void destroy_mesh();
	Mesh* get_selected_mesh();
	std::map<uint32_t, Mesh*> get_selected_meshes();
	std::map<uint32_t, std::string>& get_names();

};

