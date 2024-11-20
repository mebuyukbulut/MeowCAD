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
	auto m = meshes.find(ID);
	if (m != meshes.end()) {
		selected_mesh = (*m).second;
	}
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

	// why we use old_vertex_index
	mesh->set_vertex_index(old_vertex_index);
	mesh->set_vertex_count(mesh_vertex_count);


	vbo.write_data(old_buffer_size, mesh->get_data());
	vbo.use();

	meshes[mesh->get_ID()] = mesh;
	mesh_names[mesh->get_ID()] = mesh->get_name();

}

void MeshManager::destroy_mesh(){
	if (!selected_mesh) return;

	meshes.erase(selected_mesh->get_ID());
	mesh_names.erase(selected_mesh->get_ID());

	delete selected_mesh;
	selected_mesh = nullptr;
}

Mesh* MeshManager::get_selected_mesh() {
	return selected_mesh;
}

std::map<uint32_t, std::string>& MeshManager::get_names() {
	return mesh_names;
}