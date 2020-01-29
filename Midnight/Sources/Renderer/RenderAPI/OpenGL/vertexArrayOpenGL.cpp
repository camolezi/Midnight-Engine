#include <vertexArrayOpenGL.hpp>
#include <vertexArray.hpp>
#include <memory>
#include <glad.h>



namespace MN{

	static GLenum ShaderDataTypeToOpenGL(ShaderDataType type){
		switch(type){
			case ShaderDataType::MAT4:
			case ShaderDataType::FLOAT:
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

	uint32_t VertexArrayOpenGL::getIndexNumber() const{
		return indexBuffer->getIndexNumber();
	}

	void VertexArrayOpenGL::bind() const{
		glBindVertexArray(id);
	}

	void VertexArrayOpenGL::unbind() const{
		glBindVertexArray(0); 

	}

	VertexArrayOpenGL::~VertexArrayOpenGL(){
		vertexBuffers.clear();
		glDeleteVertexArrays(1, &id);
	}

	VertexArrayOpenGL::VertexArrayOpenGL(){
		glGenVertexArrays(1, &id);
	}


	void VertexArrayOpenGL::setVertexBuffer(const std::shared_ptr<VertexBuffer>& buffer ) {
		vertexBuffers.push_back(buffer);
		glBindVertexArray(id);
		buffer->bind();

		BufferLayout layout = buffer->getLayout();

		//For testing
		
		glVertexAttribDivisor(2, 1);
		glVertexAttribDivisor(3, 1);
		glVertexAttribDivisor(4, 1);
		glVertexAttribDivisor(5, 1);
		glVertexAttribDivisor(6, 1);
		glVertexAttribDivisor(7, 1);
		
		ASSERT(layout.getElements().size() != 0, "Vertex Buffer layout invalido");
		//TERMINAL_DEBUG(layout.getElements().size());

		for(auto& element : (layout) ){
			glEnableVertexAttribArray(attribPosition);
	    	glVertexAttribPointer(attribPosition, element.getCount(),
		    	ShaderDataTypeToOpenGL(element.getType()),
		    	element.getNormalize(), 
		    	layout.getStride(), 
		    	(void*)element.getOffset());

	    	TERMINAL_DEBUG( "Attrib:" << attribPosition <<
	    					" Count:" << element.getCount() <<
	    					" Type:" << (int)element.getType() <<
	    					" Normalize:" << element.getNormalize()<<
	    					" Stride: " << layout.getStride() <<
	    					" Offset: " << element.getOffset());

			attribPosition++;
    	}
		
	}

	void VertexArrayOpenGL::setIndexBuffer(const std::shared_ptr<IndexBuffer>& buffer ) {
		indexBuffer = buffer;
		glBindVertexArray(id);
		indexBuffer->bind();
	}


}