#pragma once

#include <vector>
#include "Vertex.h"

class Shape3D{
protected:
	std::vector<Vertex> data{};
	virtual void generate();
public:
	std::vector<Vertex> get_data() {
		if (data.empty())
			generate();

		return data;
	}



};

