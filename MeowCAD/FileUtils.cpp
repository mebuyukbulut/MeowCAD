#include "FileUtils.h"

#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

/// <summary>
/// Read the text file and return as a string
/// </summary>
/// <param name="filename">The path of the input file</param>
/// <returns></returns>
std::string FileUtils::read(const std::string& fileName) {
	std::ifstream t(fileName);
	std::stringstream buffer;
	buffer << t.rdbuf();

	return buffer.str();
}

/// <summary>
/// Read the binary file and return as a char*
/// </summary>
/// <param name="filename">The path of the input file</param>
std::vector<unsigned char> FileUtils::read_binary(const std::string& fileName){

	std::ifstream input(fileName, std::ios::binary);

	// copies all data into buffer
	return std::vector<unsigned char>(std::istreambuf_iterator<char>(input), {});
}
/// <summary>
/// Write the given std::string to text file.
/// </summary>
/// <param name="context">Given context</param>
/// <param name="filename">The path of the output file</param>
void FileUtils::write(const std::string& context, const std::string& fileName)
{
	std::ofstream myfile;
	myfile.open(fileName);
	myfile << context;
	myfile.close();
}

/// <summary>
/// Write the context to binary file.
/// </summary>
/// <param name="context">Given context</param>
/// <param name="filename">The path of the output file</param>
void FileUtils::write_binary(const char* binData,uint32_t binSize, const std::string& fileName){
	std::ofstream my_file;
	my_file.open(fileName, std::ios::out | std::ios::binary);
	my_file.write(binData, binSize);
	my_file.close();
}

// https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
std::vector<std::string> FileUtils::split(const std::string& s, char delim) {
	std::vector<std::string> result;
	std::stringstream ss(s);
	std::string item;

	while (getline(ss, item, delim)) {
		result.push_back(item);
	}

	return result;
}