#pragma once

#include <vector>
#include <string>

#include "IDGen.h"

class Material;



class MaterialManager {
//
//     SINGLETON PATTERN BEGINS
//
	MaterialManager();
public:
	static MaterialManager& get() {
		static MaterialManager instance; // Guaranteed to be destroyed.
		// Instantiated on first use.
		return instance;
	}

	MaterialManager(MaterialManager const&) = delete;
	void operator=(MaterialManager const&) = delete;
//
//     SINGLETON PATTERN ENDS
//

private:
	std::vector<Material*> materials;
	std::vector<std::string> names;
	std::vector<const char*> names_cchar;

	IDGen globalID{};
	bool dirty{ true };


	void calculate_names();
	void create_default_material();
		
public:
	~MaterialManager();
	Material* create_material();

	void destroy_material(uint32_t ID);
	void destroy_by_nameIndex(uint32_t index);
	void destroy_all();

	std::vector<Material*> get_all_materials();
	Material* get_material_by_nameIndex(uint32_t index);
	Material* get_default_material();
	std::vector<const char*>& get_names_cchar();
	//void get_IDs();

};

