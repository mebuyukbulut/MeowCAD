#pragma once
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

class FileUtils
{
public:
	std::string read(const std::string& fileName);
	std::vector<unsigned char> read_binary(const std::string& fileName);

	void write(const std::string& context, const std::string& fileName);
	void write_binary(const char* binData, uint32_t binSize, const std::string& fileName);
	std::vector<std::string> split(const std::string& s, char delim);

	
};

