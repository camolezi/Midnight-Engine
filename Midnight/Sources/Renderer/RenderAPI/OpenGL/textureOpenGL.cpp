#include <textureOpenGL.hpp>
#include <glad.h>
#include <stb_image.h>
#include <debug.hpp>


namespace MN {

	//--------------------TEXTURE 2D OPENGL -------------------------------------

	std::unique_ptr<Texture2D> Texture2D::create(const std::string& path) {
		return std::make_unique<Texture2DOpenGL>(path);
	}

	std::unique_ptr<Texture2D> Texture2D::create(unsigned int widht,unsigned int height, unsigned char* data) {
		return std::make_unique<Texture2DOpenGL>(widht,height,data);
	}
	std::unique_ptr<Texture2D> Texture2D::create() {
		return std::make_unique<Texture2DOpenGL>();
	}

	void Texture2DOpenGL::load(const std::string& path){

		stbi_set_flip_vertically_on_load(true);

		int x, y, n;
		unsigned char* data = stbi_load(path.c_str() , &x, &y, &n, 0);
		if (data == nullptr)
			TERMINAL_LOG(Log::Warning, "Error loading texture in: " << path);

		width = x;
		height = y;
		channels = n;
		
		setData(data);
		stbi_image_free(data);
	}

	void Texture2DOpenGL::setData(void* data){

		if (data == nullptr) {
			TERMINAL_LOG(Log::Warning, "Setting a texture with null data pointer");
			return;
		}

		ASSERT(width * height > 0, "Invalid size texture error");

		glBindTexture(GL_TEXTURE_2D, textureID);

		if (channels == 3) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		else if (channels == 4) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
		else {
			ASSERT(false, "Texture with invalid number of channels");
		}

		//OpenGL configs
		//Wrapping
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		//Filter
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glGenerateMipmap(GL_TEXTURE_2D);

	}

	Texture2DOpenGL::~Texture2DOpenGL(){
		glDeleteTextures(1, &textureID);
	}

	void Texture2DOpenGL::generateTexture() {
		glGenTextures(1, &textureID);
	}

	void Texture2DOpenGL::bind(int number) {
		glActiveTexture(GL_TEXTURE0 + number);
		glBindTexture(GL_TEXTURE_2D, textureID);
	}

	
	int Texture::maxNumberOfTexturesSlots() {
		//Only open GL for now
		return GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS - 5;
	}


	//-------------------TEXTURE ARRAY 2D OPEN GL-------------------------


	void Texture2DArrayOpenGL::bind() {

	}



}