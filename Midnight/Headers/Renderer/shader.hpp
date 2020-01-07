#ifndef SHADER_H
#define SHADER_H

#include <memory>

namespace MN{

	class Shader{
	public:

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual ~Shader(){}
		static std::unique_ptr<Shader> create(const std::string& vertexShaderSource, 
											  const std::string& fragmentShaderSource); 

	private:
	};

}

#endif