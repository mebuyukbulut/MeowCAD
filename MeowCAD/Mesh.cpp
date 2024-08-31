#include "Mesh.h"


void Mesh::draw(){}

void Mesh::set_ID(uint32_t ID){
	this->ID = ID;
}

void Mesh::set_name(std::string name){
	this->name = name;
}

void Mesh::set_transform(Transform transform){
	this->transform = transform;
}
void Mesh::set_material(Material* material){
	this->material = material;
}
void Mesh::set_texture(Texture* texture){
	this->texture = texture;
}

void Mesh::set_vertex_index(uint32_t vertexIndex){
	vertex_index = vertexIndex;
}
void Mesh::set_vertex_count(uint32_t vertexCount){
	vertex_count = vertexCount;
}
//void Mesh::set_data(std::vector<Vertex> data)



uint32_t Mesh::get_ID(){
	return ID;
}

std::string Mesh::get_name(){
	return name;
}

Transform Mesh::get_transform(){
	return transform;
}
Material* Mesh::get_material(){
	return material;
}
Texture* Mesh::get_texture(){
	return texture;
}

uint32_t Mesh::get_vertex_index(){
	return vertex_index;
}
uint32_t Mesh::get_vertex_count(){
	return vertex_count;
}

//std::vector<Vertex>& Mesh::get_data() 