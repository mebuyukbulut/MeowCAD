#include "MeshManager.h"

//#include "Mesh.h"
//#include "Transform.h"
//#include "VAO.h"
//#include "VBO.h"
//#include "Vertex.h"

void MeshManager::init() {
	vao.init();
	vbo.init();
	vbo.use();
	buffer_capacity = 1024 * 1024;
	vbo.allocate_data(buffer_capacity);
}

void MeshManager::select_mesh(uint32_t ID) {
	for (auto& mesh : meshes)
		if(mesh)
			if (mesh->get_ID() == ID)
				selected_mesh = mesh;
}

void MeshManager::deselect_mesh() {
	selected_mesh = nullptr;
}

void MeshManager::add_mesh(Mesh* mesh) {
	mesh->set_ID(idgen.current_ID());
	idgen.next_ID();

	int mesh_vertex_count = mesh->get_data().size();
	int old_vertex_index = vertex_index;
	vertex_index += mesh_vertex_count;

	int buffer_size_of_mesh = mesh_vertex_count * sizeof(Vertex);
	int old_buffer_size = buffer_size;
	buffer_size += buffer_size_of_mesh;

	if (buffer_size > buffer_capacity) {
		std::cout << "FATAL: Scene.h \ndata size capacity is not enough" << std::endl;
		exit(EXIT_FAILURE);
	}


	mesh->set_vertex_index(old_vertex_index);
	mesh->set_vertex_count(mesh_vertex_count);


	vbo.write_data(old_buffer_size, mesh->get_data());
	vbo.use();
	meshes.push_back(mesh);

	std::pair<std::string, uint32_t> mp;
	mp.first = mesh->get_name();
	mp.second = mesh->get_ID();
	mesh_names.push_back(mp);

}

void MeshManager::destroy_mesh(){
	if (!selected_mesh) return;

	for (auto& mesh : meshes)
		if(mesh)
			if (mesh->get_ID() == selected_mesh->get_ID())
				mesh = nullptr;
	delete selected_mesh;
	selected_mesh = nullptr;

	dirty = true;
}

Mesh* MeshManager::get_selected_mesh() {
	return selected_mesh;
}

//void MeshManager::mesh_transform(Transform newTransform) {
//	selected_mesh->set_transform(newTransform);
//}

std::vector<std::pair<std::string, uint32_t>>& MeshManager::get_names() {
	if (dirty) {
		dirty = false; 

		mesh_names.clear();

		for (auto& mesh : meshes)
			if (mesh) {
				std::pair<std::string, uint32_t> mp;
				mp.first = mesh->get_name();
				mp.second = mesh->get_ID();
				mesh_names.push_back(mp);
			}
		
	}

	return mesh_names;
}