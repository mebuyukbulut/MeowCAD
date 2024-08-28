#pragma once
#include <cstdint>
#include <vector>

#include "Transform.h"
#include "Material.h"
#include "Texture.h"
#include "Vertex.h"


class Mesh{
	uint32_t ID;

	uint32_t vertex_index;
	uint32_t vertex_count; 
	std::vector<Vertex> data{};

	Transform transform;	
	Material* material{};
	Texture* texture{};
	

public:
	void draw();

	void set_transform(Transform transform);
	void set_material(Material* material);
	void set_texture(Texture* texture);

	void set_vertex_index(uint32_t vertexIndex);
	void set_vertex_count(uint32_t vertexCount);
	void set_data(std::vector<Vertex> data) {
		this->data = data;
	}


	Transform get_transform();
	Material* get_material();
	Texture*  get_texture();

	uint32_t get_vertex_index();
	uint32_t get_vertex_count();
	std::vector<Vertex>& get_data() {
		return data;
	}



};

