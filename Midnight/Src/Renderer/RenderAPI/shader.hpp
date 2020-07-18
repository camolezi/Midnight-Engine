#ifndef SHADER_H
#define SHADER_H

#include <memory>
#include <coreMath.hpp>
#include <string>

namespace MN{

	class Shader{
	public:

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		//Uniforms (temporary)
	    virtual void uniformVec3( const std::string& name, const vec3& data) const = 0;
		virtual void uniformVec4( const std::string& name, const vec4& data) const = 0;
		virtual void uniformMat4( const std::string& name, const mat4& data) const = 0;
		virtual void uniformInt(const std::string& name, int data) const = 0;
		virtual void uniformIntArray(const std::string& name, int* data, int size) const = 0;

		virtual ~Shader(){}
		static std::unique_ptr<Shader> create(const std::string& vertexShaderSource, 
											  const std::string& fragmentShaderSource); 

	private:
	};

}

#endif