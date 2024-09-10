#pragma once
#include <cstdint>

// Unique ID generator
class IDGen{
	uint32_t index;

public:
	IDGen();
	IDGen(uint32_t firstID);

	uint32_t current_ID();
	uint32_t next_ID();


};

