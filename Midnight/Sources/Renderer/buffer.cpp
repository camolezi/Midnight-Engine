#include <vertexBufferOpenGL.hpp>
#include <indexBufferOpenGL.hpp>


namespace MN{

	std::unique_ptr<VertexBuffer> VertexBuffer::create(uint32_t size, float * data){
		//Just OpenGL for now
		return std::make_unique<VertexBufferOpenGL>(size,data);
	}


	std::unique_ptr<IndexBuffer> IndexBuffer::create(uint32_t size, uint32_t * indices){

		return std::make_unique<IndexBufferOpenGL>(size,indices);
	}
}
