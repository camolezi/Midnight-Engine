#ifndef VERTEXBUFFEROPENGL_H
#define VERTEXBUFFEROPENGL_H


#include <vertexBuffer.hpp>
#include <glad.h>


namespace MN{

	class VertexBufferOpenGL : public VertexBuffer{

		public:
			void bind() const override ;
			void unbind() const override;
			//void setLayout(BufferLayout& layout) override{this->layout = layout;}
			void updateData(uint32_t size, void* data) override;

			void setLayout(BufferLayout layout) override{this->layout = layout;};
			const BufferLayout& getLayout() const override{return layout;};	

			VertexBufferOpenGL(uint32_t size, void * data, VertexBuffer::type type = VertexBuffer::type::StaticDraw);
			~VertexBufferOpenGL();

		private:
			unsigned int id;
			BufferLayout layout;
			VertexBuffer::type _type;
			//BufferLayout& layout;
	};

}


#endif