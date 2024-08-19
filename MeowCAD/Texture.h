#pragma once
#include <cstdint>
#include <string>

// Is it best way? 
#define GL_TEXTURE0 0x84C0

class Texture{
	uint32_t ID{};
	unsigned char* data{};
public:
	~Texture();

	void init(const std::string& file);
	void use(uint32_t textureUnit = GL_TEXTURE0);
};

