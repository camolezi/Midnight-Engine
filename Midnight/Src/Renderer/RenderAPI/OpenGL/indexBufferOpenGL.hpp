#ifndef INDEXBUFFEROPENGL_H
#define INDEXBUFFEROPENGL_H


#include <indexBuffer.hpp>


namespace MN{

	class IndexBufferOpenGL : public IndexBuffer{

	public:
		void bind() const override ;
		void unbind() const override;

		IndexBufferOpenGL(uint32_t size, uint32_t * indices);
		~IndexBufferOpenGL();

		uint32_t getIndexNumber() const override;

	private:
		unsigned int id;
		uint32_t size;

	};

}


#endif