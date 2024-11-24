#pragma once

#include "Texture.h"
#include <string>

class TextureManager{
	Texture sky, radiance, irradiance;

public:
	void init_skybox(std::string path);
	void use_skybox();
};

