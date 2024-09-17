#include "Scene.h"

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

	for (unsigned int i = 0; i < sizeof(lightPositions) / sizeof(lightPositions[0]); ++i)
	{
		glm::vec3 newPos = lightPositions[i];// +glm::vec3(sin(glfwGetTime() * 5.0) * 5.0, 0.0, 0.0);
		newPos = lightPositions[i];
		shader.set("lightPositions[" + std::to_string(i) + "]", newPos);
		shader.set("lightColors[" + std::to_string(i) + "]", lightColors[i]);

		//model = glm::mat4(1.0f);
		//model = glm::translate(model, newPos);
		//model = glm::scale(model, glm::vec3(0.5f));
		//shader.setMat4("model", model);
		//shader.setMat3("normalMatrix", glm::transpose(glm::inverse(glm::mat3(model))));
		//renderSphere();
	}



	//// lighting
	//glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

	//shader.set("light.position", lightPos);
	//shader.set("light.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
	//shader.set("light.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
	//shader.set("light.specular;", glm::vec3(1.0f, 1.0f, 1.0f));

	// Cubemap 

	cubemap_shader.init("shaders/skybox.vs", "shaders/skybox.fs");
	load_cube_map();
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
	Mesh* cubemap = new Mesh;
	Transform t;
	t.set_scale(glm::vec3(FLT_MAX, FLT_MAX, FLT_MAX));
	cubemap->set_data(Cube(1).get_data());
	cubemap->set_ID(999'999);
	add_mesh(cubemap);

}

void Scene::load_cube_map() {
	// load textures
	// -------------
	//unsigned int cubeTexture = loadTexture("resources/textures/container.jpg");
	std::string file = "images/cubemaps/";
	std::vector<std::string> faces{
		file + "px.png",
		file + "nx.png",
		file + "py.png",
		file + "ny.png",
		file + "pz.png",
		file + "nz.png"
	};
	//unsigned int cubemapTexture = loadCubemap(faces);


	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	stbi_set_flip_vertically_on_load(false);
	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++) {
		unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data) {
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else {
			std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}

	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	cubemapTexture = textureID;
}

void Scene::draw_cubemap() {
	cubemap_shader.use();


	//skyboxShader.setMat4("view", view);
	//skyboxShader.setMat4("projection", projection);

	auto i = meshes[0];

	//i->get_material()->use(&shader);

	//glm::mat4 model = i->get_transform().get_model_matrix();
	glm::mat4 projection = camera.get_projection();
	glm::mat4 view = glm::mat4(glm::mat3(camera.get_view())); // remove translation from the view matrix


	//cubemap_shader.set("model", model);
	cubemap_shader.set("view", view);
	cubemap_shader.set("projection", projection);

	//shader.set("viewPos", camera.get_position());
	//std::cout << camera.get_position().x;
	//std::cout << i->get_vertex_index() << "\t" << i->get_vertex_count() << "\n";
	//shader.set();
	glDrawArrays(GL_TRIANGLES, i->get_vertex_index(), i->get_vertex_count());// i->get_data_index(), i->get_data_size());

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