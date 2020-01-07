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

			void setLayout(BufferLayout layout) override{this->layout = layout;};
			const BufferLayout& getLayout() const override{return layout;};	

			VertexBufferOpenGL(uint32_t size, float * data);
			~VertexBufferOpenGL();

		private:
			unsigned int id;
			BufferLayout layout;
			//BufferLayout& layout;
	};

}


#endif