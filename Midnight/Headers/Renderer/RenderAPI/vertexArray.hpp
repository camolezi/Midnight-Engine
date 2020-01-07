#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include <memory>
#include <vertexBuffer.hpp>
#include <indexBuffer.hpp>

	
//This is class will only be used in openGL, others API may have a empty implementation?
namespace MN{

	//Will support only one Buffer of each type

	class VertexArray{
	public:
		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void setVertexBuffer(const std::shared_ptr<VertexBuffer>& buffer ) = 0;
		virtual void setIndexBuffer(const std::shared_ptr<IndexBuffer>& buffer ) = 0;

		virtual ~VertexArray(){};

		static std::unique_ptr<VertexArray> create();
	};
}


#endif