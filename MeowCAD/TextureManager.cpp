#include "TextureManager.h"

#include <vector>
#include <glad/glad.h>

void TextureManager::init_skybox(std::string path){
	std::string sky_file = path + "skybox/output_skybox_";
	std::string radiance_file = path + "radiance/output_skybox_";
	std::string irradiance_file = path + "irradiance/output_skybox_";

	std::vector<std::string> sky_faces, radiance_faces, irradiance_faces;
	std::vector<std::string> faces{
		"posx.hdr",			"negx.hdr",			"posy.hdr",
		"negy.hdr",			"posz.hdr",			"negz.hdr"
	};

	for (int i{}; i < 6; i++) sky_faces.push_back(sky_file + faces[i]);
	for (int i{}; i < 6; i++) radiance_faces.push_back(radiance_file + faces[i]);
	for (int i{}; i < 6; i++) irradiance_faces.push_back(irradiance_file + faces[i]);


	sky.init(sky_faces);
	radiance.init(radiance_faces);
	irradiance.init(irradiance_faces);

	use_skybox();
}
void TextureManager::use_skybox(){
	sky.use(GL_TEXTURE0, GL_TEXTURE_CUBE_MAP);
	radiance.use(GL_TEXTURE1, GL_TEXTURE_CUBE_MAP);
	irradiance.use(GL_TEXTURE2, GL_TEXTURE_CUBE_MAP);
}