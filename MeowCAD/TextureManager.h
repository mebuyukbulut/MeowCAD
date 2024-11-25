#pragma once

#include "Texture.h"
#include <string>


class TextureManager{
	Texture sky, radiance, irradiance;

public:
	void init_skybox(std::string path);
	void use_skybox();
	void use_material(Texture* albedo=nullptr, Texture* arm = nullptr, Texture* normal = nullptr);
};

