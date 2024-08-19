#pragma once
#include <cstdint>

class VAO{
	uint32_t ID{};

public:
	VAO() = default;
	~VAO();
	void init();
};

