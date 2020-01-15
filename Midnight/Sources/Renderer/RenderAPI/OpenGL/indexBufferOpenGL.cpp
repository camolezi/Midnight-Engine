#include <indexBufferOpenGL.hpp>

#include <glad.h>

namespace MN{

	void IndexBufferOpenGL::bind() const{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id); 
	}

	void IndexBufferOpenGL::unbind() const{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); 
	}

	IndexBufferOpenGL::IndexBufferOpenGL(uint32_t size, uint32_t * indices){
		this->size = size;
		glGenBuffers(1, &id);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
	}

	uint32_t IndexBufferOpenGL::getIndexNumber() const{
		return size;
	}

	IndexBufferOpenGL::~IndexBufferOpenGL(){
		glDeleteBuffers(1,&id);
	}

}

