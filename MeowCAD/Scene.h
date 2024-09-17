#pragma once

#include "Camera.h"
#include "VAO.h"
#include "VBO.h"
#include "Mesh.h"
#include "Shader.h"
#include "ETime.h"

#include <vector>
#include <glad/glad.h>

#include "Cube.h"
#include <stb_image.h>

class Scene{
	ETime time;
	Camera camera;

	VAO vao;
	VBO vbo;

	Shader shader;
	Shader cubemap_shader;
	unsigned int cubemapTexture;
	std::vector<Mesh*> meshes;
	std::vector<std::pair<std::string, uint32_t>> mesh_names;
	Mesh* selected_mesh{};

	int buffer_size{};
	int buffer_capacity{};
	int vertex_index{};

	// maybe we need a dirty flag for update 
public:

	void init();

	void load_cube_map();
	void draw_cubemap();
	void draw();

	void select_mesh(uint32_t ID);
	void deselect_mesh();
	void add_mesh(Mesh* mesh);
	//void destroy_mesh();
	Mesh* get_selected_mesh();
	void mesh_transform(Transform newTransform);


	std::vector<std::pair<std::string, uint32_t>>& get_names();
	Camera& get_camera();
	ETime& get_time();
	~Scene();
};

