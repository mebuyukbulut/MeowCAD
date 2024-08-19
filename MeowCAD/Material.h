#pragma once
#include <glm/gtc/type_ptr.hpp>

class Shader;


struct MaterialInfo {
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
};
class Material{
    MaterialInfo material_info{};
    Shader* shader;
    
public:

    void init(MaterialInfo materialInfo, Shader* shader);
    void use();
};

