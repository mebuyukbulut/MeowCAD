#include "Scene.h"
#include "Mesh.h"

#include <glad/glad.h>

#include "Cube.h"
#include <stb_image.h>

void Scene::init() {
	vao.init();
	vbo.init();
	vbo.use();
	buffer_capacity = 1024 * 1024;
	vbo.allocate_data(buffer_capacity);

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



	add_mesh(skybox.init(&camera));

}

void Scene::draw() {
	time.update();
	shader.use();
	shader.set("time", time.get_elapsed_time());

	for (auto i : meshes) {
		if (i->get_ID() == meshes[0]->get_ID())
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



void Scene::select_mesh(uint32_t ID) {
	for (auto& mesh : meshes)
		if (mesh->get_ID() == ID)
			selected_mesh = mesh;
}
void Scene::deselect_mesh() {
	selected_mesh = nullptr;
}
void Scene::add_mesh(Mesh* mesh) {
	int mesh_vertex_count = mesh->get_data().size();
	int old_vertex_index = vertex_index;
	vertex_index += mesh_vertex_count;

	int buffer_size_of_mesh = mesh_vertex_count * sizeof(Vertex);
	int old_buffer_size = buffer_size;
	buffer_size += buffer_size_of_mesh;

	if (buffer_size > buffer_capacity) {
		std::cout << "FATAL: Scene.h \ndata size capacity is not enough" << std::endl;
		exit(EXIT_FAILURE);
	}


	mesh->set_vertex_index(old_vertex_index);
	mesh->set_vertex_count(mesh_vertex_count);


	vbo.write_data(old_buffer_size, mesh->get_data());
	vbo.use();
	meshes.push_back(mesh);

	std::pair<std::string, uint32_t> mp;
	mp.first = mesh->get_name();
	mp.second = mesh->get_ID();
	mesh_names.push_back(mp);

}

//void destroy_mesh();
Mesh* Scene::get_selected_mesh() {
	return selected_mesh;
}

void Scene::mesh_transform(Transform newTransform) {
	selected_mesh->set_transform(newTransform);
}



std::vector<std::pair<std::string, uint32_t>>& Scene::get_names() {
	return mesh_names;
}

Camera& Scene::get_camera() { return camera; }
ETime& Scene::get_time() { return time; }
Scene::~Scene() {
	// Delete meshes 
	// Delete other resources 
}