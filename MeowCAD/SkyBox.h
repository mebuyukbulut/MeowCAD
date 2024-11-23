#pragma once
#include <glad/glad.h>
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
#include "stb_image.h"
#include "Cube.h"


class SkyBox{
	Shader cubemap_shader;

	unsigned int load_texture(std::vector<std::string> faces) {

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

		//glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
		return textureID;
	}


public:
	Camera* camera;
	Mesh* mesh;


	unsigned int skybox_cubemap;
	unsigned int radiance_cubemap;
	unsigned int irradiance_cubemap;



	Mesh* init(Camera* camera) {
		this->camera = camera;
		cubemap_shader.init("shaders/skybox.vs", "shaders/skybox.fs");
		

		std::string skybox_file = "images/skybox/ocean/skybox/output_skybox_";
		std::string radiance_file = "images/skybox/ocean/radiance/output_skybox_";
		std::string irradiance_file = "images/skybox/ocean/irradiance/output_skybox_";

		std::vector<std::string> skybox_faces, radiance_faces, irradiance_faces;
		std::vector<std::string> faces{
			"posx.hdr",			"negx.hdr",			"posy.hdr",
			"negy.hdr",			"posz.hdr",			"negz.hdr"
		};

		for (int i{}; i < 6; i++) skybox_faces.push_back(skybox_file + faces[i]);
		for (int i{}; i < 6; i++) radiance_faces.push_back(radiance_file + faces[i]);
		for (int i{}; i < 6; i++) irradiance_faces.push_back(irradiance_file + faces[i]);
		


		skybox_cubemap = load_texture(skybox_faces);
		radiance_cubemap = load_texture(radiance_faces);
		irradiance_cubemap = load_texture(irradiance_faces);



		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, skybox_cubemap);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_CUBE_MAP, radiance_cubemap);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_CUBE_MAP, irradiance_cubemap);



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

