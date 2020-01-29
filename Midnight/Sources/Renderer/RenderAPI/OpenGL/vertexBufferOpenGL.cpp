#include <vertexBufferOpenGL.hpp>


namespace MN{

	void VertexBufferOpenGL::bind() const{
		glBindBuffer(GL_ARRAY_BUFFER, id); 
	}

	void VertexBufferOpenGL::unbind() const{
		glBindBuffer(GL_ARRAY_BUFFER, 0); 
	}

	VertexBufferOpenGL::VertexBufferOpenGL(uint32_t size, void * data, VertexBuffer::type type){
		_type = type;
		glGenBuffers(1, &id);
		glBindBuffer(GL_ARRAY_BUFFER, id);
    	glBufferData(GL_ARRAY_BUFFER, size, data,(GLenum)type);
	}

	void VertexBufferOpenGL::updateData(uint32_t size, void* data) {
		glBindBuffer(GL_ARRAY_BUFFER, id);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
	}

	VertexBufferOpenGL::~VertexBufferOpenGL(){
		glDeleteBuffers(1,&id);
	}
}

