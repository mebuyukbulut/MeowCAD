#include "Shader.h"
#include <glad/glad.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "FileUtils.h"
#include <filesystem>
#include <fstream>
#include <iostream>

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



    std::cout << shader_name << " is caching...\n";

    //BEGIN/ https://gist.github.com/yeaFern/ecd60a9bb93cb75ef9c4f775cb1d9f3f
    // Get the size of the binary.
    GLint binaryLength = 0;
    glGetProgramiv(shaderProgram, GL_PROGRAM_BINARY_LENGTH, &binaryLength);

    // Allocate space for the binary, as well as the binary format.
    size_t bufferSize = sizeof(GLenum) + binaryLength;
    char* binary = new char[sizeof(GLenum) + binaryLength];

    // Get the binary from the driver, saving the format.
    GLenum binaryFormat;
    glGetProgramBinary(shaderProgram, binaryLength, nullptr, &binaryFormat, binary+ sizeof(GLenum));
    
    // Prefix the binary with the format.
    *((GLenum*)binary) = binaryFormat;

    //END/https://gist.github.com/yeaFern/ecd60a9bb93cb75ef9c4f775cb1d9f3f
    
    FileUtils fu;
    fu.write_binary(binary, bufferSize, "shaders/cache/" + shader_name + ".bin");

    std::cout << shader_name << " cached to:\t" << ("shaders/cache/" + shader_name + ".bin") << "\n";


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

bool Shader::load_from_cache(){
    std::filesystem::path directoryPath = std::filesystem::current_path();
    std::string stringpath = directoryPath.generic_string();
    stringpath += "/shaders/cache/" + shader_name + ".bin";

    if (std::filesystem::exists(stringpath)) {
        FileUtils fu;
        auto my_data = fu.read_binary(stringpath);

        // Read it into a buffer.
        char* buffer = new char[my_data.size()];
        std::copy(my_data.begin(), my_data.end(), buffer);
        

        // Grab the format from the front of the buffer;
        GLenum format = *((GLenum*)buffer);

        // Calculate offset to start of the shader binary.
        void* binaryStart = buffer + sizeof(GLenum);
        size_t binaryLength = my_data.size() - sizeof(GLenum);


        uint32_t shaderProgram = glCreateProgram();
        // Upload the binary.
        glProgramBinary(shaderProgram, format, binaryStart, binaryLength);

        // Clean up.
        delete[] buffer;

        // Check for success.
        GLint success = 0;
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (success) {
            std::cout << shader_name << " loaded from cache succesful" << std::endl;
            ID = shaderProgram;
            return true;
        }
    }
    
    return false;
}


Shader::~Shader(){
    glDeleteProgram(ID);
}

void Shader::init(const std::string& shaderName, const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath) {
    shader_name = shaderName;

    if (load_from_cache())
        return;
    std::cout << shader_name << " is compiling...\n";

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
