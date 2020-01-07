#ifndef VERTEXBUFFER_HPP
#define VERTEXBUFFER_HPP

#include <memory>
#include <vector>
#include <string>
#include <debug.hpp>
#include <initializer_list>
#include <iterator>

namespace MN{


	//Represent one type of element
	enum class ShaderDataType{
		FLOAT2,
		FLOAT3,
		FLOAT4
	};

	class LayoutElement{
	public:

		LayoutElement(ShaderDataType type,std::string name, bool normalize = false):
			type{type}, 
			name{name},
			normalize{normalize}{ calculateSize();}

		int getSize(){return _size;}
		int getOffset(){return offset;}
		std::string getName(){return name;}
		bool getNormalize(){return normalize;}
		int getCount(){return count;}
		int offset;

	private:
		void calculateSize();

		ShaderDataType type;
		std::string name;
		bool normalize;

		//need to calculate
		int _size; //In bytes
		int count; //In elements
		
	};

	// BufferLayout layout= {FLOAT3, name = "Position" , normalized = false}

	//has a list of layout Element - One layout Element describe a single vertex attribute 
	class BufferLayout{
	public:
	
		BufferLayout(std::vector<LayoutElement> elements):elements{elements}
			{calculateStride();}
		BufferLayout(std::initializer_list<LayoutElement> elements):elements{elements}
			{calculateStride();}

		BufferLayout(){};

		//Iterators
		std::vector<LayoutElement>::iterator begin() { return elements.begin(); }
		std::vector<LayoutElement>::iterator end() { return elements.end(); }

		int getStride(){return stride;}
		std::vector<LayoutElement>& getElements(){return elements;}
	private:
		void calculateStride();
		//How many bytes one vertex has
		int stride = 0;
		std::vector<LayoutElement> elements;

	};

	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	class VertexBuffer{
		public:

			virtual void bind() const= 0;
			virtual void unbind() const = 0;

			virtual void setLayout(BufferLayout layout) = 0;
			virtual const BufferLayout& getLayout() const = 0;	

			static std::unique_ptr<VertexBuffer> create(uint32_t size, float * data);

			virtual ~VertexBuffer(){}

	};

}



#endif