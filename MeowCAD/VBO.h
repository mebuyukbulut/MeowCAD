#pragma once
#include <cstdint>
#include <vector>

class Vertex;

class VBO{
	uint32_t ID{};

public:
	VBO() = default;
	~VBO();

	void init();
	void bind_data(std::vector<Vertex>& data);
	void allocate_data(int byteSize);
	void write_data(int offset, std::vector<Vertex>& data);
	void use();
};

