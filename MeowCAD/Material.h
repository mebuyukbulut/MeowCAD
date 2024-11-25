#pragma once
#include <glm/gtc/type_ptr.hpp>
#include <string>

class Shader;
class Texture;

struct MaterialInfo {
    glm::vec3 albedo{1,1,1};
    float metallic{};
    float roughness{0.3};
    float ao{0.1};

    Texture* albedo_tex{};
    Texture* arm_tex{};
    Texture* normal_tex{};

    bool operator !=(MaterialInfo lhs) {
        return
            albedo != lhs.albedo ||
            metallic != lhs.metallic ||
            roughness != lhs.roughness ||
            ao != lhs.ao; 
    }
};
struct MaterialID {
    uint32_t ID;
    std::string name;

    MaterialID() = default;
    MaterialID(uint32_t ID, std::string name) : ID{ ID }, name{ name } {}
};


class Material{
    MaterialID ID;
public:
    MaterialInfo material_info{};
    
    void init(MaterialInfo materialInfo, MaterialID ID);
    void use(Shader* shader);

    MaterialInfo get();
    void set(MaterialInfo materialInfo);
        
    //std::string& get_name() {
    //    return name; 
    //}
    MaterialID get_ID() {
        return ID;
    }

    
};

