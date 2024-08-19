#include "VAO.h"
#include <glad/glad.h>

VAO::~VAO(){
	glDeleteVertexArrays(1, &ID);
}

void VAO::init()
{
	glGenVertexArrays(1, &ID);
	glBindVertexArray(ID);
}
