#include<shaderOpenGL.hpp>
#include<debug.hpp>
#include<glad.h>

namespace MN{

	//Only openGL for now
	std::unique_ptr<Shader> Shader::create(const std::string& vertexShaderSource, 	
										  const std::string& fragmentShaderSource)
	{
		return std::make_unique<ShaderOpenGL>(vertexShaderSource,fragmentShaderSource);
	}



	ShaderOpenGL::ShaderOpenGL(const std::string& vertexShaderSource, const std::string& fragmentShaderSource){

		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		const GLchar * vertexSrc =(const GLchar *) vertexShaderSource.c_str();

	    glShaderSource(vertexShader, 1, &vertexSrc, NULL);
	    glCompileShader(vertexShader);
	    // check for shader compile errors
	    int success;
	    char infoLog[512];
	    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	    if (!success)
	    {
	        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
	        ASSERT(false,"Vertex Shader Error in Compilation:\n" << infoLog );
	    }
	    // fragment shader
	    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	    const GLchar * fragSrc = (const GLchar *)fragmentShaderSource.c_str();
	    glShaderSource(fragmentShader, 1, &fragSrc, NULL);
	    glCompileShader(fragmentShader);
	    // check for shader compile errors
	    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	    if (!success){
	        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
	       	ASSERT(false,"Pixel Shader Error in Compilation:\n" << infoLog );
	    }
	    // link shaders
	    shaderProgram = glCreateProgram();
	    glAttachShader(shaderProgram, vertexShader);
	    glAttachShader(shaderProgram, fragmentShader);
	    glLinkProgram(shaderProgram);
	    // check for linking errors
	    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	    if (!success) {
	        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
	        ASSERT(false,"Shader Program Linking Error:\n" << infoLog);
	    }
	    
	    glDeleteShader(vertexShader);
	    glDeleteShader(fragmentShader);
	}

	void ShaderOpenGL::unbind() const{
		glUseProgram(0);
	}

	void ShaderOpenGL::bind() const{
		glUseProgram(shaderProgram);
	}

	ShaderOpenGL::~ShaderOpenGL(){
		glDeleteProgram(shaderProgram);
	}


	void ShaderOpenGL::uniformVec3( const std::string& name,const  vec3& data) const{
		int uniformLocation = glGetUniformLocation(shaderProgram, name.c_str());
		ASSERT( uniformLocation != -1, "Shader Uniform not found Vec3: " << name);
		glUniform3f(uniformLocation, data.at(0), data.at(1), data.at(2));
	}

	void ShaderOpenGL::uniformVec4( const std::string& name,const vec4& data) const{
		int uniformLocation = glGetUniformLocation(shaderProgram, name.c_str());
		ASSERT( uniformLocation != -1, "Shader Uniform not found Vec4: " << name);
		glUniform4f(uniformLocation, data.at(0), data.at(1), data.at(2), data.at(3));
	}

	void ShaderOpenGL::uniformMat4( const std::string& name,const mat4& data) const{
		int uniformLocation = glGetUniformLocation(shaderProgram, name.c_str());
		ASSERT( uniformLocation != -1, "Shader Uniform not found Vec4: " << name);
		glUniformMatrix4fv(uniformLocation,1,true,static_cast<const float *>(data.getData()) );
	}

	void ShaderOpenGL::uniformInt(const std::string& name, int data) const{
		int uniformLocation = glGetUniformLocation(shaderProgram, name.c_str());
		ASSERT(uniformLocation != -1, "Shader Uniform not found int: " << name);
		glUniform1i(uniformLocation, data);
	}

	void ShaderOpenGL::uniformIntArray(const std::string& name, int* data, int size) const
	{
		int uniformLocation = glGetUniformLocation(shaderProgram, name.c_str());
		ASSERT(uniformLocation != -1, "Shader Uniform not found int: " << name);
		glUniform1iv(uniformLocation, size, data);

	}



}