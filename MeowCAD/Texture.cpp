#include "Texture.h"

#include <glad/glad.h>
#include <iostream>
#include "LogUtils.h"

#ifndef STB_IMAGE_IMPLEMENTATION
	#define STB_IMAGE_IMPLEMENTATION
#endif // !STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


Texture::~Texture(){
    glDeleteBuffers(1, &ID);
}

/// <summary>
/// This function loads 2d textures 
/// </summary>
/// <param name="file"></param>
void Texture::init(const std::string& file){
    //unsigned int texture;
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);

    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // load and generate the texture
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(file.c_str(), &width, &height, &nrChannels, 0);
    if (data){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else{
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    use();
}

/// <summary>
/// This function load skybox cubemap textures
/// </summary>
/// <param name="faces">Adress of 6 faces</param>
void Texture::init(std::vector<std::string> faces){
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    stbi_set_flip_vertically_on_load(false);
    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++) {
        unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        else
            LogUtils::get().log("Cubemap texture failed to load at path: " + faces[i], LogType::error);
            //std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
        
        stbi_image_free(data);

    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    //glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    ID = textureID;
}

/// <summary>
/// Bind the texture to given target. 
/// </summary>
/// <param name="textureUnit">GL_TEXTURE0, GL_TEXTURE1, ...</param>
/// <param name="textureType">GL_TEXTURE_2D, GL_TEXTURE_CUBE_MAP, ...</param>
void Texture::use(uint32_t textureUnit, uint32_t textureType){
    // bind Texture
    glActiveTexture(textureUnit);
    glBindTexture(textureType, ID);
}

void load_texture() {

}