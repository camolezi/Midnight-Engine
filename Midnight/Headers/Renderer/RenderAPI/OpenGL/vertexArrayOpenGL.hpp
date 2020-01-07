#ifndef VERTEXARRAYOPENGL_H
#define VERTEXARRAYOPENGL_H

#include <vertexArray.hpp>

namespace MN{


	class VertexArrayOpenGL : public VertexArray{
	public:

		void bind() const override;
		void unbind() const override;

		void setVertexBuffer(const std::shared_ptr<VertexBuffer>& buffer ) override;
		void setIndexBuffer(const std::shared_ptr<IndexBuffer>& buffer ) override;

		 ~VertexArrayOpenGL();
		 VertexArrayOpenGL();
	private:
		unsigned int id;

		std::shared_ptr<VertexBuffer> vertexBuffer;
		std::shared_ptr<IndexBuffer> indexBuffer;
	};
}



#endif