#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H

#include <memory>

namespace MN{

	class IndexBuffer{
		public:
			virtual void bind() const= 0;
			virtual void unbind() const = 0;

			static std::unique_ptr<IndexBuffer> create(uint32_t size, uint32_t * indices);

			virtual ~IndexBuffer(){}


	};
}




#endif