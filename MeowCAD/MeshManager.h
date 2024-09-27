#pragma once

#include <iostream>
#include <vector>

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

	bool dirty = true;

	std::vector<std::pair<std::string, uint32_t>> mesh_names;
public:
	// we need a better approach instead of using std::vector
	std::vector<Mesh*> meshes;
	Mesh* selected_mesh{};


	void init();

	void select_mesh(uint32_t ID);
	void deselect_mesh();
	void add_mesh(Mesh* mesh);

	void destroy_mesh();
	Mesh* get_selected_mesh();
	void mesh_transform(Transform newTransform);
	std::vector<std::pair<std::string, uint32_t>>& get_names();

};

