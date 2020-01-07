#include <vertexBufferOpenGL.hpp>

namespace MN{

	std::unique_ptr<VertexBuffer> VertexBuffer::create(uint32_t size, float * data){
		//Just OpenGL for now
		return std::make_unique<VertexBufferOpenGL>(size,data);
	}
}
