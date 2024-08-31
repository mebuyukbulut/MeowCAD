#pragma once
#include <cstdint>
#include <vector>
#include <string>

#include "Transform.h"
#include "Material.h"
#include "Texture.h"
#include "Vertex.h"


class Mesh{
	uint32_t ID;
	std::string name;

	uint32_t vertex_index;
	uint32_t vertex_count; 
	std::vector<Vertex> data{};

	Transform transform;	
	Material* material{};
	Texture* texture{};
	

public:
	void draw();

	void set_ID(uint32_t ID);
	void set_name(std::string name);

	void set_transform(Transform transform);
	void set_material(Material* material);
	void set_texture(Texture* texture);

	void set_vertex_index(uint32_t vertexIndex);
	void set_vertex_count(uint32_t vertexCount);
	void set_data(std::vector<Vertex> data) {
		this->data = data;
	}



	uint32_t get_ID();
	std::string get_name();

	Transform get_transform();
	Material* get_material();
	Texture*  get_texture();

	uint32_t get_vertex_index();
	uint32_t get_vertex_count();
	std::vector<Vertex>& get_data() {
		return data;
	}



};

