#include "MaterialManager.h"

#include <string>
#include "Material.h"

MaterialManager::MaterialManager() {	
	create_default_material();
}
void MaterialManager::calculate_names(){
	names.clear();
	names_cchar.clear();

	for (Material* material : materials)
		names.push_back(material->get_ID().name);

	for (std::string& i : names)
		names_cchar.push_back(i.data());
}
void MaterialManager::create_default_material(){
	auto def_mat = new Material();
	def_mat->init({}, MaterialID(0, "Default Material"));
	materials.push_back(def_mat);
	dirty = true;
}
MaterialManager::~MaterialManager(){
	destroy_all();
}

Material* MaterialManager::create_material() {
	Material* material = new Material();
	uint32_t mat_ID = globalID.next_ID();
	std::string mat_name = "material " + std::to_string(mat_ID);
	material->init({}, MaterialID(mat_ID,mat_name));
	materials.push_back(material);
	dirty = true;
	return material;
}

void MaterialManager::destroy_material(uint32_t ID){
	auto pos = find_if(materials.begin(), materials.end(), 
		[&](Material* i) { return i->get_ID().ID == ID; }	
	);
	delete *pos;
	materials.erase(pos);
	dirty = true;
}
void MaterialManager::destroy_by_nameIndex(uint32_t index) {
	auto pos = materials.begin() + index;
	delete *pos;
	materials.erase(pos);
	dirty = true;
}

void MaterialManager::destroy_all(){
	for (auto material : materials)
		delete material;
	materials.clear();
	dirty = true;
}

std::vector<Material*> MaterialManager::get_all_materials(){
	return materials;
}

Material* MaterialManager::get_material_by_nameIndex(uint32_t index){
	return materials[index];
}

Material* MaterialManager::get_default_material() {
	if (materials.empty())
		create_default_material();
	return materials[0];
}
std::vector<const char*>& MaterialManager::get_names_cchar(){
	if (dirty) {
		calculate_names();
		dirty = false; 
	}
	return names_cchar;
}
