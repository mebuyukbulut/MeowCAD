#pragma once

#include "Camera.h"
#include "VAO.h"
#include "VBO.h"
#include "Mesh.h"
#include "Shader.h"
#include "ETime.h"

#include <vector>
#include <glad/glad.h>

class Scene{
	ETime time;

	Camera camera;

	VAO vao;
	VBO vbo;

	Shader shader;

	std::vector<Mesh*> meshes;
	int buffer_size{};
	int buffer_capacity{};
	int vertex_index{};

public:

	void init() {
		vao.init();
		vbo.init();
		vbo.use();
		buffer_capacity = 1024*1024;
		vbo.allocate_data(buffer_capacity);

		shader.init("shaders/material.vert", "shaders/material.frag");
		shader.use();


		// lighting
		glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

		shader.set("light.position", lightPos);
		shader.set("light.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
		shader.set("light.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
		shader.set("light.specular;", glm::vec3(1.0f, 1.0f, 1.0f));



		
	}
	void draw() {
		time.update();
		shader.use(); 
		shader.set("time", time.get_elapsed_time());

		for (auto i : meshes) {
			i->get_material()->use(&shader);

			glm::mat4 model = i->get_transform().get_model_matrix();
			glm::mat4 projection = camera.get_projection();
			glm::mat4 view = camera.get_view();


			shader.set("model", model);
			shader.set("view", view);
			shader.set("projection", projection);

			shader.set("viewPos", camera.get_position());
			//std::cout << camera.get_position().x;
			//std::cout << i->get_vertex_index() << "\t" << i->get_vertex_count() << "\n";
			//shader.set();
			glDrawArrays(GL_TRIANGLES, i->get_vertex_index(),i->get_vertex_count());// i->get_data_index(), i->get_data_size());
		}
	}



	void add_mesh(Mesh* mesh) {
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
	}
	//void destroy_mesh();

	Camera& get_camera() { return camera; }
	ETime& get_time() { return time; }
	~Scene() {
		// Delete meshes 
		// Delete other resources 
	}
};

