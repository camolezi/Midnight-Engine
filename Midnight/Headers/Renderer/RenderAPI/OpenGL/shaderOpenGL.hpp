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

		void uniformVec3(const std::string& name,const vec3& data) const override;
		void uniformVec4(const std::string& name,const vec4& data) const override;
		void uniformMat4(const std::string& name,const mat4& data) const override;


		~ShaderOpenGL();

	private:
		int shaderProgram;
	};
}





#endif