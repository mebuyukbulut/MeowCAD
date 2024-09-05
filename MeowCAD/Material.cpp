#include "Material.h"
#include "Shader.h"


void Material::init(MaterialInfo materialInfo){
    material_info = materialInfo;
    //this->shader = shader;
}

void Material::use(Shader* shader){
    shader->set("albedo",   material_info.albedo);
    shader->set("metallic",   material_info.metallic);
    shader->set("roughness",  material_info.roughness);
    shader->set("ao", material_info.ao);
}

//uniform vec3 albedo;
//uniform float metallic;
//uniform float roughness;
//uniform float ao;