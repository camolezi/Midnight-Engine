#ifndef VERTEXBUFFER_HPP
#define VERTEXBUFFER_HPP

#include <memory>

namespace MN{

	class VertexBuffer{
		public:

			virtual void bind() const= 0;
			virtual void unbind() const = 0;

			static std::unique_ptr<VertexBuffer> create(uint32_t size, float * data);

			virtual ~VertexBuffer(){}

	};

}



#endif