#include "Vertex.h"

void Vertex::set_position(glm::vec3 position) {
	this->position[0] = position.x;
	this->position[1] = position.y;
	this->position[2] = position.z;
}
void Vertex::set_normal(glm::vec3 normal){
	this->normal[0] = normal.x;
	this->normal[1] = normal.y;
	this->normal[2] = normal.z;
}
void Vertex::set_color(glm::vec4 color){
	this->color[0] = color.x;
	this->color[1] = color.y;
	this->color[2] = color.z;
	this->color[3] = color.w;
}
void Vertex::set_tex_coord(glm::vec2 tex_coord){
	this->tex_coord[0] = tex_coord.x;
	this->tex_coord[1] = tex_coord.y;
}



glm::vec3 Vertex::get_position(){
	return glm::vec3(
		position[0],
		position[1],
		position[2]
	);
}
glm::vec3 Vertex::get_normal(){
	return glm::vec3(
		normal[0],
		normal[1],
		normal[2]	
	);
}
glm::vec4 Vertex::get_color(){
	return glm::vec4(
		color[0],
		color[1],
		color[2],
		color[3]
	);
}
glm::vec2 Vertex::get_tex_coord(){
	return glm::vec2(
		tex_coord[0],
		tex_coord[1]
	);

}
