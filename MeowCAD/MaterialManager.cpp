#include "MaterialManager.h"

#include <string>
#include "Material.h"

MaterialManager::MaterialManager() {	
	default_material = new Material();
	default_material->init({}, MaterialID( 0, "Default Material"));
}
MaterialManager::~MaterialManager(){
	if (default_material) delete default_material;
	destroy_all();
}

Material* MaterialManager::create_material() {
	Material* material = new Material();
	uint32_t mat_ID = globalID.next_ID();
	std::string mat_name = "material " + std::to_string(mat_ID);
	material->init({}, MaterialID(mat_ID,mat_name));
	materials.push_back(material);
	return material;
}

void MaterialManager::destroy_material(uint32_t ID){
	auto pos = find_if(materials.begin(), materials.end(), 
		[&](Material* i) { return i->get_ID().ID == ID; }	
	);
	delete *pos;
	materials.erase(pos);
}

void MaterialManager::destroy_all(){
	for (auto material : materials)
		delete material;
	materials.clear();
}

std::vector<Material*> MaterialManager::get_all_materials(){
	return materials;
}
