#pragma once
#include <cstdint>
#include <string>
#include <vector>

// Is it best way? 
#define GL_TEXTURE0 0x84C0
#define GL_TEXTURE_2D 0x0DE1


class Texture{
	uint32_t ID{};
	//unsigned char* data{}; // Are we need data after load to GPU
public:
	~Texture();

	void init(const std::string& file);
	void init(std::vector<std::string> faces);
	void use(uint32_t textureUnit = GL_TEXTURE0, uint32_t textureType = GL_TEXTURE_2D);
};

