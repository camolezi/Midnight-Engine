#ifndef VERTEXARRAYOPENGL_H
#define VERTEXARRAYOPENGL_H

#include <vertexArray.hpp>
#include <vector>

namespace MN{


	class VertexArrayOpenGL : public VertexArray{
	public:

		void bind() const override;
		void unbind() const override;

		void setVertexBuffer(const std::shared_ptr<VertexBuffer>& buffer ) override;
		void setIndexBuffer(const std::shared_ptr<IndexBuffer>& buffer ) override;

		uint32_t getIndexNumber() const override;


		 ~VertexArrayOpenGL();
		 VertexArrayOpenGL();
	private:
		unsigned int id;
		int attribPosition = 0;

		std::vector<std::shared_ptr<VertexBuffer>> vertexBuffers;
		std::shared_ptr<IndexBuffer> indexBuffer;
	};
}



#endif