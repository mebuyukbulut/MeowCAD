#pragma once
#include <glm/gtc/type_ptr.hpp>
#include <string>

class Shader;

struct MaterialInfo {
    glm::vec3 albedo{1,1,1};
    float metallic{};
    float roughness{0.3};
    float ao{0.1};

    bool operator !=(MaterialInfo lhs) {
        return
            albedo != lhs.albedo ||
            metallic != lhs.metallic ||
            roughness != lhs.roughness ||
            ao != lhs.ao; 
    }
};


class Material{    
    uint32_t ID; 
    std::string name; 

    MaterialInfo material_info{};
    //Shader* shader;
    
public:
    void init(MaterialInfo materialInfo, uint32_t materialID, std::string name);
    void use(Shader* shader);

    MaterialInfo get();
    void set(MaterialInfo materialInfo);

    
    std::string& get_name() {
        return name; 
    }
    uint32_t get_ID() {
        return ID;
    }

    
};

