#include "Material.h"
#include "Shader.h"


void Material::init(MaterialInfo materialInfo, uint32_t ID, std::string name){
    material_info = materialInfo;
    this->ID = ID; 
    this->name = name; 

    //this->shader = shader;
}

void Material::use(Shader* shader){
    shader->set("albedo",   material_info.albedo);
    shader->set("metallic",   material_info.metallic);
    shader->set("roughness",  material_info.roughness);
    shader->set("ao", material_info.ao);
}

MaterialInfo Material::get(){
    return material_info;
}

void Material::set(MaterialInfo materialInfo){
    material_info = materialInfo;
}


