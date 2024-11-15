#include "Shader.h"
#include <glad/glad.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "FileUtils.h"

uint32_t Shader::link_program(uint32_t vertexShader, uint32_t fragmentShader) {
    // link shaders
    uint32_t shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // check for linking errors
    int success;
    char infoLog[1024];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 1024, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    return shaderProgram;
}

uint32_t Shader::compile_shader(std::string code, uint32_t type) {
    unsigned int myShader = glCreateShader(type);
    const char* ccode = code.c_str();
    glShaderSource(myShader, 1, &ccode, NULL);
    glCompileShader(myShader);


    // check for shader compile errors
    int success;
    char infoLog[1024];
    glGetShaderiv(myShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(myShader, 1024, NULL, infoLog);
        std::cout << "ERROR::SHADER::"
            << (GL_VERTEX_SHADER == type ? "VERTEX":"FRAGMENT")
            << "::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    return myShader;
}

int Shader::get_loc(std::string& uniform_name)
{
    if (uniform_locations.find(uniform_name) != uniform_locations.end()) {
        //std::cout << "b";
        return uniform_locations[uniform_name];
    }
    else {
        //std::cout << "a";
        const char* cchar = uniform_name.c_str();
        int vertexColorLocation = glGetUniformLocation(ID, cchar);
        uniform_locations[uniform_name] = vertexColorLocation;
        return vertexColorLocation;
    }
}


Shader::~Shader(){
    glDeleteProgram(ID);
}

void Shader::init(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath) {

    FileUtils fu;
    auto vertex_code = fu.read(vertexShaderFilePath);
    auto fragment_code = fu.read(fragmentShaderFilePath);


    uint32_t vertexShader = compile_shader(vertex_code, GL_VERTEX_SHADER);
    uint32_t fragmentShader = compile_shader(fragment_code, GL_FRAGMENT_SHADER);
    ID = link_program(vertexShader, fragmentShader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::use(){
    glUseProgram(ID);
}

void Shader::set(std::string uniform_name, float value) {
    glUseProgram(ID);
    glUniform1f(get_loc(uniform_name), value);
}
//void Shader::set(std::string uniform_name, int value) {
//    glUseProgram(ID);
//    glUniform1i(get_loc(uniform_name), value);
//}

void Shader::set(std::string uniform_name, glm::vec3 value) {
    glUseProgram(ID);
    glUniform3f(get_loc(uniform_name), value.x,value.y,value.z);
}

void Shader::set(std::string uniform_name, glm::mat4 value) {
    glUseProgram(ID);
    glUniformMatrix4fv(get_loc(uniform_name), 1, GL_FALSE, glm::value_ptr(value));
}
void Shader::set(std::string uniform_name, glm::mat3 value) {
    glUseProgram(ID);
    glUniformMatrix3fv(get_loc(uniform_name), 1, GL_FALSE, glm::value_ptr(value));
}
