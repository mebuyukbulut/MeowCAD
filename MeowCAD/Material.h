#pragma once
#include <glm/gtc/type_ptr.hpp>

class Shader;


struct MaterialInfo {
    glm::vec3 albedo;
    float metallic;
    float roughness;
    float ao;
};
class Material{
    MaterialInfo material_info{};
    //Shader* shader;
    
public:

    void init(MaterialInfo materialInfo);
    void use(Shader* shader);
};

