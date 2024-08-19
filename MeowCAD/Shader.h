#pragma once
#include <cstdint>
#include <string>
#include <map>
#include <glm/mat4x4.hpp>

class Shader{
	std::map<std::string, int> uniform_locations;

	uint32_t ID{};

	uint32_t link_program(uint32_t vertexShader, uint32_t fragmentShader);
	uint32_t compile_shader(std::string code, uint32_t type);

	int get_loc(std::string& uniform_name);

public:
	Shader() = default;
	~Shader();

	void init(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
	void use();

	void set(std::string uniform_name, float value);
	void set(std::string uniform_name, glm::mat4 value);
	void set(std::string uniform_name, glm::vec3 value);
};

