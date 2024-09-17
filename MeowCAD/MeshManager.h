#pragma once

#include "Mesh.h"
#include "Transform.h"
#include "VAO.h"
#include "VBO.h"
#include <iostream>

#include <vector>

class MeshManager{
public:
	VAO vao;
	VBO vbo;

	std::vector<Mesh*> meshes;
	std::vector<std::pair<std::string, uint32_t>> mesh_names;
	Mesh* selected_mesh{};

	int buffer_size{};
	int buffer_capacity{};
	int vertex_index{};

	void init() {
		vao.init();
		vbo.init();
		vbo.use();
		buffer_capacity = 1024 * 1024;
		vbo.allocate_data(buffer_capacity);
	}



	//void select_mesh(uint32_t ID);
	//void deselect_mesh();
	//void add_mesh(Mesh* mesh);
	////void destroy_mesh();
	//Mesh* get_selected_mesh();
	//void mesh_transform(Transform newTransform);

	//std::vector<std::pair<std::string, uint32_t>>& get_names();



	void select_mesh(uint32_t ID) {
		for (auto& mesh : meshes)
			if (mesh->get_ID() == ID)
				selected_mesh = mesh;
	}
	void deselect_mesh() {
		selected_mesh = nullptr;
	}
	void add_mesh(Mesh* mesh) {
		int mesh_vertex_count = mesh->get_data().size();
		int old_vertex_index = vertex_index;
		vertex_index += mesh_vertex_count;

		int buffer_size_of_mesh = mesh_vertex_count * sizeof(Vertex);
		int old_buffer_size = buffer_size;
		buffer_size += buffer_size_of_mesh;

		if (buffer_size > buffer_capacity) {
			std::cout << "FATAL: Scene.h \ndata size capacity is not enough" << std::endl;
			exit(EXIT_FAILURE);
		}


		mesh->set_vertex_index(old_vertex_index);
		mesh->set_vertex_count(mesh_vertex_count);


		vbo.write_data(old_buffer_size, mesh->get_data());
		vbo.use();
		meshes.push_back(mesh);

		std::pair<std::string, uint32_t> mp;
		mp.first = mesh->get_name();
		mp.second = mesh->get_ID();
		mesh_names.push_back(mp);

	}

	//void destroy_mesh();
	Mesh* get_selected_mesh() {
		return selected_mesh;
	}

	void mesh_transform(Transform newTransform) {
		selected_mesh->set_transform(newTransform);
	}



	std::vector<std::pair<std::string, uint32_t>>& get_names() {
		return mesh_names;
	}

};

