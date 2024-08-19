#include "VBO.h"
#include <glad/glad.h>
#include <iostream>
#include "Vertex.h"

VBO::~VBO(){
	glDeleteBuffers(1, &ID);
}

void VBO::bind_data(std::vector<Vertex>& data){
	//for (auto i : data)
	//	std::cout << i << ", ";

	use();
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(Vertex), data.data(), GL_STATIC_DRAW);
}

void VBO::use(){ // ?
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::init() {
	glGenBuffers(1, &ID);
	use(); // ? 


	// VertexAttributes
	// 
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(1);
	// color attribute
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glEnableVertexAttribArray(2);
	// texture attribute
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tex_coord));
	glEnableVertexAttribArray(3);
}
