#include <vertexArrayOpenGL.hpp>
#include <vertexArray.hpp>
#include <memory>
#include <glad.h>



namespace MN{

	static GLenum ShaderDataTypeToOpenGL(ShaderDataType type){
		switch(type){
			case ShaderDataType::FLOAT2: 
			case ShaderDataType::FLOAT3: 
			case ShaderDataType::FLOAT4: 
				return GL_FLOAT;
			default:
				ASSERT(false, "Invalid shader data type");
				return -1;
		};
	}

	std::unique_ptr<VertexArray> VertexArray::create(){
		return std::make_unique<VertexArrayOpenGL>();
	}


	void VertexArrayOpenGL::bind() const{
		glBindVertexArray(id);
	}

	void VertexArrayOpenGL::unbind() const{
		glBindVertexArray(0); 

	}

	VertexArrayOpenGL::~VertexArrayOpenGL(){
		glDeleteVertexArrays(1, &id);
	}

	VertexArrayOpenGL::VertexArrayOpenGL(){
		glGenVertexArrays(1, &id);
	}


	void VertexArrayOpenGL::setVertexBuffer(const std::shared_ptr<VertexBuffer>& buffer ) {
		vertexBuffer = buffer;
		glBindVertexArray(id);
		vertexBuffer->bind();

		BufferLayout layout = buffer->getLayout();

		int position = 0;
		for(auto& element : (layout) ){
			glEnableVertexAttribArray(position);  
	    	glVertexAttribPointer(position, element.getCount(),
		    	ShaderDataTypeToOpenGL(ShaderDataType::FLOAT3),
		    	element.getNormalize(), 
		    	layout.getStride(), 
		    	(void*)element.getOffset());
    	}
		
	}

	void VertexArrayOpenGL::setIndexBuffer(const std::shared_ptr<IndexBuffer>& buffer ) {
		indexBuffer = buffer;
		glBindVertexArray(id);
		indexBuffer->bind();
	}


}