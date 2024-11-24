#pragma once

#include <vector>

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
	Shader shader;
	ETime time;

	TextureManager texture_manager;
	Texture albedo, arm, normal, brdf_lut;
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
};

