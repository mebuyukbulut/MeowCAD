#pragma once

#include <glad/glad.h>
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
#include "stb_image.h"
#include "Cube.h"
#include "MeshManager.h"
#include <bitset>


class MeshSelector{

	Shader shader;
	MeshManager* mesh_manager{};

public:
	Camera* camera;
	Mesh* mesh;


	void init(Camera* camera, MeshManager* mesh_manager) {
		this->camera = camera;
		this->mesh_manager = mesh_manager;
		shader.init("shaders/mesh_selector.vs", "shaders/mesh_selector.fs");
	}

	void draw() {
		shader.use();

		for (auto i : mesh_manager->meshes) {
			if (!i) continue;
			if (i->get_ID() == mesh_manager->meshes[0]->get_ID())
				continue;

			glm::mat4 model = i->get_transform().get_model_matrix();
			glm::mat4 projection = camera->get_projection();
			glm::mat4 view = camera->get_view();
			shader.set("model", model);
			shader.set("view", view);
			shader.set("projection", projection);

			//
			//std::bitset<32> color_bitset{ i->get_ID()};
			float ID = i->get_ID() / 255.0 * 5.0;
			glm::vec3 color = glm::vec3(ID, ID, ID);

			

			shader.set("IDcolor", color);


			glDrawArrays(GL_TRIANGLES, i->get_vertex_index(), i->get_vertex_count());
		}
	}
};

