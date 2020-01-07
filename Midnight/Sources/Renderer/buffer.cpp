#include <vertexBufferOpenGL.hpp>
#include <indexBufferOpenGL.hpp>


namespace MN{

	// -------------------- LayoutElement ----------------------------------

	void LayoutElement::calculateSize(){
		switch(this->type){
			case ShaderDataType::FLOAT2: count = 2; _size = 2 * sizeof(float); break;
			case ShaderDataType::FLOAT3: count = 3; _size = 3 * sizeof(float); break;
			case ShaderDataType::FLOAT4: count = 4; _size = 4 * sizeof(float); break;
			default: ASSERT(false, "Invalid Shader Data Type"); break;
		};
	}
		
	//----------------------- Buffer Layout -----------------------------------

	void BufferLayout::calculateStride(){
		for(auto& element : elements){
			element.offset = stride;
			stride += element.getSize();
		}
	}

	//--------------------------Vertex Buffer -----------------------------------

	std::unique_ptr<VertexBuffer> VertexBuffer::create(uint32_t size, float * data){
		//Just OpenGL for now
		return std::make_unique<VertexBufferOpenGL>(size,data);
	}


	//---------------------------Index Buffer----------------------------------

	std::unique_ptr<IndexBuffer> IndexBuffer::create(uint32_t size, uint32_t * indices){

		return std::make_unique<IndexBufferOpenGL>(size,indices);
	}
}
