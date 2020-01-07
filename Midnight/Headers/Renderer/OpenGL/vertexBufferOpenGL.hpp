#ifndef VERTEXBUFFEROPENGL_H
#define VERTEXBUFFEROPENGL_H


#include <vertexBuffer.hpp>
#include <glad.h>


namespace MN{

	class VertexBufferOpenGL : public VertexBuffer{

		public:
			void bind() const override ;
			void unbind() const override;

			VertexBufferOpenGL(uint32_t size, float * data);
			~VertexBufferOpenGL();

		private:
			unsigned int id;

	};
}


#endif