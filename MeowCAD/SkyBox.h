#pragma once
#include <glad/glad.h>
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
#include "stb_image.h"
#include "Cube.h"


class SkyBox{
	Shader cubemap_shader;
	unsigned int cubemapTexture;

public:
	Camera* camera;
	Mesh* mesh;


	Mesh* init(Camera* camera) {
		this->camera = camera;
		cubemap_shader.init("shaders/skybox.vs", "shaders/skybox.fs");
		
		// load cube map


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






		//


		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		mesh = new Mesh;
		Transform t;
		t.set_scale(glm::vec3(FLT_MAX, FLT_MAX, FLT_MAX));
		mesh->set_data(Cube(1).get_data());
		mesh->set_ID(999'999);

		return mesh;
	}
	void draw() {
		cubemap_shader.use();


		//skyboxShader.setMat4("view", view);
		//skyboxShader.setMat4("projection", projection);

		auto i = mesh;// meshes[0];

		//i->get_material()->use(&shader);

		//glm::mat4 model = i->get_transform().get_model_matrix();
		glm::mat4 projection = camera->get_projection();
		glm::mat4 view = glm::mat4(glm::mat3(camera->get_view())); // remove translation from the view matrix


		//cubemap_shader.set("model", model);
		cubemap_shader.set("view", view);
		cubemap_shader.set("projection", projection);

		//shader.set("viewPos", camera.get_position());
		//std::cout << camera.get_position().x;
		//std::cout << i->get_vertex_index() << "\t" << i->get_vertex_count() << "\n";
		//shader.set();
		glDrawArrays(GL_TRIANGLES, i->get_vertex_index(), i->get_vertex_count());// i->get_data_index(), i->get_data_size());

	}
};

