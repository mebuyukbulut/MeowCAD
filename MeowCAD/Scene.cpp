#include "Scene.h"
#include "Mesh.h"

#include <glad/glad.h>

#include "Cube.h"
#include <stb_image.h>


#include <glm/gtc/matrix_transform.hpp>

void Scene::init() {
	mesh_manager.init();
	mesh_selector.init(&camera, &mesh_manager);

	shader.init("shaders/pbr.vs", "shaders/pbr.fs");
	shader.use();

	glm::vec3 lightPositions[] = {
		glm::vec3(-10.0f,  10.0f, 10.0f),
		glm::vec3(10.0f,  10.0f, 10.0f),
		glm::vec3(-10.0f, -10.0f, 10.0f),
		glm::vec3(10.0f, -10.0f, 10.0f),
	};
	glm::vec3 lightColors[] = {
		glm::vec3(300.0f, 300.0f, 300.0f),
		glm::vec3(300.0f, 300.0f, 300.0f),
		glm::vec3(300.0f, 300.0f, 300.0f),
		glm::vec3(300.0f, 300.0f, 300.0f)
	};

	for (unsigned int i = 0; i < sizeof(lightPositions) / sizeof(lightPositions[0]); ++i)	{
		glm::vec3 newPos = lightPositions[i];// +glm::vec3(sin(glfwGetTime() * 5.0) * 5.0, 0.0, 0.0);
		newPos = lightPositions[i];
		shader.set("lightPositions[" + std::to_string(i) + "]", newPos);
		shader.set("lightColors[" + std::to_string(i) + "]", lightColors[i]);
	}


	// Cubemap 
	auto cubemap_mesh = skybox.init(&camera);
	mesh_manager.add_mesh(cubemap_mesh);
}

void Scene::draw() {
	shader.use();
	shader.set("time", (float)time.get_elapsed_time());

	shader.set("modeFlag", 0);
	if (auto m = mesh_manager.get_selected_mesh()) {
		shader.set("modeFlag", 1.0);

		m->get_material()->use(&shader);

		glm::mat4 model = m->get_transform().get_model_matrix() * glm::scale(glm::mat4(1.0f), glm::vec3(1.1));
		glm::mat4 projection = camera.get_projection();
		glm::mat4 view = camera.get_view();


		shader.set("model", model);
		shader.set("view", view);
		shader.set("projection", projection);
		shader.set("normalMatrix", glm::transpose(glm::inverse(glm::mat3(model))));

		shader.set("camPos", camera.get_position());

		glDrawArrays(GL_TRIANGLES, m->get_vertex_index(), m->get_vertex_count());
		glClear(GL_DEPTH_BUFFER_BIT);

		shader.set("modeFlag", 0);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	for (auto i : mesh_manager.meshes) {
		if (!i) continue;
		if (i->get_ID() == mesh_manager.meshes[0]->get_ID())
			continue;
		i->get_material()->use(&shader);

		glm::mat4 model = i->get_transform().get_model_matrix();
		glm::mat4 projection = camera.get_projection();
		glm::mat4 view = camera.get_view();


		shader.set("model", model);
		shader.set("view", view);
		shader.set("projection", projection);
		shader.set("normalMatrix", glm::transpose(glm::inverse(glm::mat3(model))));

		shader.set("camPos", camera.get_position());
		//std::cout << camera.get_position().x;
		//std::cout << i->get_vertex_index() << "\t" << i->get_vertex_count() << "\n";
		//shader.set();
		glDrawArrays(GL_TRIANGLES, i->get_vertex_index(), i->get_vertex_count());// i->get_data_index(), i->get_data_size());
	}
}

Camera& Scene::get_camera() { return camera; }

ETime& Scene::get_time() { return time; }
Scene::~Scene() {
	// Delete meshes 
	// Delete other resources 
}