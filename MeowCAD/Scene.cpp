#include "Scene.h"
#include "Mesh.h"

#include <glad/glad.h>

#include "Cube.h"
#include <stb_image.h>


#include <glm/gtc/matrix_transform.hpp>

void Scene::init() {	
	brdf_lut.init("images/ibl_brdf_lut.png");

	mesh_manager.init();
	mesh_selector.init(&camera, &mesh_manager);

	pbr_shader.init("pbr","shaders/pbr.vs", "shaders/pbr.fs");
	activate_pbr();
	matcap_shader.init("matcap", "shaders/matcap.vs", "shaders/matcap.fs");
	activate_matcap();

	Texture* matcap = new Texture(); // memory leak
	matcap->init("images/matcap/ceramic_lightbulb.jpg");
;
	texture_manager.use_matcap(matcap);

	glm::vec3 lightPositions[] = {
		glm::vec3(-10.0f,  10.0f, 10.0f),
		glm::vec3(10.0f,  10.0f, 10.0f),
		glm::vec3(-10.0f, -10.0f, 10.0f),
		glm::vec3(10.0f, -10.0f, 10.0f),
	};
	glm::vec3 lightColors[] = {
		glm::vec3(600),
		glm::vec3(600),
		glm::vec3(600),
		glm::vec3(600)
	};

	for (unsigned int i = 0; i < sizeof(lightPositions) / sizeof(lightPositions[0]); ++i)	{
		glm::vec3 newPos = lightPositions[i];// +glm::vec3(sin(glfwGetTime() * 5.0) * 5.0, 0.0, 0.0);
		newPos = lightPositions[i];
		shader->set("lightPositions[" + std::to_string(i) + "]", newPos);
		shader->set("lightColors[" + std::to_string(i) + "]", lightColors[i]);
	}


	// Cubemap 
	load_skybox("meadow");
	//texture_manager.init_skybox("images/skybox/ocean/");
	//texture_manager.use_skybox();
	auto cubemap_mesh = skybox.init(&camera);
	mesh_manager.add_mesh(cubemap_mesh);
}

void Scene::draw() {
	shader->use();
	shader->set("time", (float)time.get_elapsed_time());

	// We draw an orange outline for selected meshes 
	shader->set("modeFlag", 0);
	for (auto m : mesh_manager.get_selected_meshes()) {
		shader->set("modeFlag", 1.0);

		//m->get_material()->use(&shader);

		glm::mat4 model = m.second->get_transform().get_model_matrix() * glm::scale(glm::mat4(1.0f), glm::vec3(1.1));
		glm::mat4 projection = camera.get_projection();
		glm::mat4 view = camera.get_view();



		shader->set("model", model);
		shader->set("view", view);
		shader->set("projection", projection);
		shader->set("normalMatrix", glm::transpose(glm::inverse(glm::mat3(model))));
			  
		shader->set("camPos", camera.get_position());

		glDrawArrays(GL_TRIANGLES, m.second->get_vertex_index(), m.second->get_vertex_count());
		glClear(GL_DEPTH_BUFFER_BIT);

		shader->set("modeFlag", 0);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}


	brdf_lut.use(GL_TEXTURE6); // probably we dont need that each time

	// We draw all meshes
	for (auto m : mesh_manager.meshes) {
		Mesh* i = m.second;

		if (!i) continue; // null check
		if (i->get_ID() == mesh_manager.meshes[0]->get_ID())
			continue; // first mesh is skybox so we continue
		
		//Assign material and textures
		Material* mat = i->get_material();
		mat->use(shader);
		texture_manager.use_material(
			mat->material_info.albedo_tex,
			mat->material_info.arm_tex,
			mat->material_info.normal_tex
		);



		// set transforms
		glm::mat4 model = i->get_transform().get_model_matrix();
		glm::mat4 projection = camera.get_projection();
		glm::mat4 view = camera.get_view();


		shader->set("model", model);
		shader->set("view", view);
		shader->set("projection", projection);
		shader->set("normalMatrix", glm::transpose(glm::inverse(glm::mat3(model))));
			  
		shader->set("camPos", camera.get_position());
		//std::cout << camera.get_position().x;
		//std::cout << i->get_vertex_index() << "\t" << i->get_vertex_count() << "\n";
		//shader.set();
		glDrawArrays(GL_TRIANGLES, i->get_vertex_index(), i->get_vertex_count());// i->get_data_index(), i->get_data_size());
	}
}

Camera& Scene::get_camera() { return camera; }

ETime& Scene::get_time() { return time; }
void Scene::load_skybox(std::string name)
{
	texture_manager.init_skybox("images/skybox/"+name+"/");
	texture_manager.use_skybox();
}
void Scene::load_matcap(std::string name){
	Texture* matcap = new Texture(); // memory leak
	
	matcap->init("images/matcap/"+ name);
	
	texture_manager.use_matcap(matcap);
}
void Scene::activate_pbr(){
	shader = &pbr_shader;
	shader->use();
}
void Scene::activate_matcap(){
	shader = &matcap_shader;
	shader->use();
}
Scene::~Scene() {
	// Delete meshes 
	// Delete other resources 
}