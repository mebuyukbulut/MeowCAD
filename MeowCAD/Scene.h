#pragma once

#include <vector>

#include "Camera.h"
#include "ETime.h"
#include "VAO.h"
#include "VBO.h"
#include "Shader.h"
#include "Transform.h"
#include "SkyBox.h"
#include "MeshManager.h"
#include "MeshSelector.h"
class Mesh;

class Scene{
	//ETime time;
	Camera camera;
	Shader shader;


	// maybe we need a dirty flag for update 
public:
	ETime time;

	SkyBox skybox;
	MeshManager mesh_manager; 
	MeshSelector mesh_selector;
	~Scene();

	void init();
	void draw();




	Camera& get_camera();
	ETime& get_time();
};

