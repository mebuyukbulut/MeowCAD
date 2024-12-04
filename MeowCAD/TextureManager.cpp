#include "TextureManager.h"

#include <vector>
#include <glad/glad.h>

void TextureManager::init_skybox(std::string path){
	Texture* old_sky{}, * old_rad{}, * old_irrad{};

	if (sky) {
		old_sky = sky;
		old_rad = radiance;
		old_irrad = irradiance;
	}
	std::string sky_file = path + "skybox/output_skybox_";
	std::string radiance_file = path + "radiance/output_skybox_";
	std::string irradiance_file = path + "irradiance/output_skybox_";

	std::vector<std::string> sky_faces, radiance_faces, irradiance_faces;
	std::string postfix = ".jpg";
	std::vector<std::string> faces{
		"posx",			"negx",			"posy",
		"negy",			"posz",			"negz"
	};
	for (auto& f : faces)
		f += postfix;

	for (int i{}; i < 6; i++) sky_faces.push_back(sky_file + faces[i]);
	for (int i{}; i < 6; i++) radiance_faces.push_back(radiance_file + faces[i]);
	for (int i{}; i < 6; i++) irradiance_faces.push_back(irradiance_file + faces[i]);

	sky = new Texture();
	radiance = new Texture();
	irradiance = new Texture();
	sky->init(sky_faces);
	radiance->init(radiance_faces);
	irradiance->init(irradiance_faces);

	use_skybox();

	// THERE ARE an error here
	// 
	//if (old_sky) {
	//	delete old_sky;
	//	delete old_rad;
	//	delete old_irrad;
	//}
}
void TextureManager::use_skybox(){
	sky->use(GL_TEXTURE0, GL_TEXTURE_CUBE_MAP);
	radiance->use(GL_TEXTURE1, GL_TEXTURE_CUBE_MAP);
	irradiance->use(GL_TEXTURE2, GL_TEXTURE_CUBE_MAP);
}

void TextureManager::use_material(Texture* albedo, Texture* arm, Texture* normal){
	if(albedo)
		albedo->use(GL_TEXTURE3);
	if(arm)
		arm->use(GL_TEXTURE4);
	if(normal)
		normal->use(GL_TEXTURE5);
}

void TextureManager::use_matcap(Texture* matcap){
	if (matcap)
		matcap->use(GL_TEXTURE7);
}


