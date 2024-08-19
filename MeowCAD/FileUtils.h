#pragma once
#include <string>
#include <sstream>
#include <fstream>


class FileUtils
{
public:
	std::string read(const std::string& filename) {
		std::ifstream t(filename);
		std::stringstream buffer;
		buffer << t.rdbuf();

		return buffer.str();
	}
};

