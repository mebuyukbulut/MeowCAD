#pragma once

#include <vector>

#include "Camera.h"
#include "ETime.h"
#include "VAO.h"
#include "VBO.h"
#include "Shader.h"
#include "Transform.h"
#include "SkyBox.h"

class Mesh;

class Scene{
	ETime time;
	Camera camera;

	VAO vao;
	VBO vbo;

	Shader shader;
	std::vector<Mesh*> meshes;
	std::vector<std::pair<std::string, uint32_t>> mesh_names;
	Mesh* selected_mesh{};

	int buffer_size{};
	int buffer_capacity{};
	int vertex_index{};

	// maybe we need a dirty flag for update 
public:
	SkyBox skybox;
	~Scene();

	void init();

	//void load_cube_map();
	//void draw_cubemap();
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
};

