#pragma once
#include <glad/glad.h>
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
#include "stb_image.h"
#include "Cube.h"


class SkyBox{
	Shader cubemap_shader;

public:
	Camera* camera;
	Mesh* mesh;

	Mesh* init(Camera* camera) {
		this->camera = camera;
		cubemap_shader.init("shaders/skybox.vs", "shaders/skybox.fs");
		
		mesh = new Mesh;
		Transform t;
		t.set_scale(glm::vec3(FLT_MAX, FLT_MAX, FLT_MAX));
		mesh->set_data(Cube(1).get_data());

		return mesh;
	}

	void draw() {
		cubemap_shader.use();

		auto i = mesh;// meshes[0];


		//glm::mat4 model = i->get_transform().get_model_matrix();
		glm::mat4 projection = camera->get_projection();
		glm::mat4 view = glm::mat4(glm::mat3(camera->get_view())); // remove translation from the view matrix


		//cubemap_shader.set("model", model);
		cubemap_shader.set("view", view);
		cubemap_shader.set("projection", projection);


		glDrawArrays(GL_TRIANGLES, i->get_vertex_index(), i->get_vertex_count());
	}
};

