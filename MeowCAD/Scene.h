#pragma once

#include <vector>
#include <string>

#include "Camera.h"
#include "ETime.h"
#include "VAO.h"

#include "VBO.h"
#include "Shader.h"
#include "Transform.h"

#include "SkyBox.h"
#include "TextureManager.h"
#include "MeshManager.h"
#include "MeshSelector.h"

class Mesh;

class Scene{
	Camera camera;
	Shader pbr_shader, matcap_shader;
	Shader* shader; 
	ETime time;

	TextureManager texture_manager;
	Texture brdf_lut;
	// maybe we need a dirty flag for update 
public:
	SkyBox skybox;

	MeshManager mesh_manager; 
	MeshSelector mesh_selector;
	~Scene();

	void init();
	void draw();


	Camera& get_camera();
	ETime& get_time();
	void load_skybox(std::string name);
	void load_matcap(std::string name);

	void activate_pbr();
	void activate_matcap();
};

