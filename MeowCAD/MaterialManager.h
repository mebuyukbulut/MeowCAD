#pragma once

#include <vector>
#include "IDGen.h"

class Material;

class MaterialManager {
//
//     SINGLETON PATTERN BEGINS
//
	MaterialManager() = default;
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
	IDGen globalID{};
		
public:
	~MaterialManager();
	Material* create_material();
	void destroy_material(uint32_t ID);
	void destroy_all();
	std::vector<Material*> get_all_materials();
};

