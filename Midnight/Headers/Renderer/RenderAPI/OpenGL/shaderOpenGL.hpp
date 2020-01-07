#ifndef SHADEROPENGL_H
#define SHADEROPENGL_H

#include <shader.hpp>
#include <string>

namespace MN{

	class ShaderOpenGL : public Shader{
	public:
		ShaderOpenGL(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
		void bind() const override;
		void unbind() const override;

		~ShaderOpenGL();

	private:
		int shaderProgram;
	};
}





#endif