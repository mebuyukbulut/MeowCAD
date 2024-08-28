#include "Material.h"
#include "Shader.h"


void Material::init(MaterialInfo materialInfo){
    material_info = materialInfo;
    //this->shader = shader;
}

void Material::use(Shader* shader){
    shader->set("material.ambient",   material_info.ambient);
    shader->set("material.diffuse",   material_info.diffuse);
    shader->set("material.specular",  material_info.specular);
    shader->set("material.shininess", material_info.shininess);
}
