#include <textureOpenGL.hpp>
#include <glad.h>
#include <stb_image.h>
#include <debug.hpp>


namespace MN {

	std::unique_ptr<Texture2D> Texture2D::create(const std::string& path) {
		return std::make_unique<Texture2DOpenGL>(path);
	}



	void Texture2DOpenGL::load(const std::string& path){

		stbi_set_flip_vertically_on_load(true);

		int x, y, n;
		unsigned char* data = stbi_load(path.c_str() , &x, &y, &n, 0);
		//ASSERT(data != nullptr, "Error loading texture in: " << path);

		width = x;
		height = y;
		channels = n;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8	, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		
		stbi_image_free(data);
		//OpenGL config

		//Wrapping
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		//Filter
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}

	Texture2DOpenGL::~Texture2DOpenGL(){
		glDeleteTextures(1, &textureID);
	}

	void Texture2DOpenGL::generateTexture() {
		glGenTextures(1, &textureID);
	}

	void Texture2DOpenGL::bind() {
		glBindTextureUnit(0, textureID);
	}

	

}