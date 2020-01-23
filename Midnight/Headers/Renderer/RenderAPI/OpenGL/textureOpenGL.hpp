#ifndef TEXTUREOPENGL_HPP
#define TEXTUREOPENGL_HPP

#include <texture.hpp>

namespace MN {

	class Texture2DOpenGL : public Texture2D {
	public:
		void bind() override;
		void load(const std::string& path) override;
		void setData(void* data) override;

		void setSize(unsigned int width, unsigned int height) override { this->width = width; this->height = height;};

		~Texture2DOpenGL();

		Texture2DOpenGL() : width{ 0 }, height{ 0 }, channels{ 0 } {generateTexture(); };
		Texture2DOpenGL(const std::string& path) { generateTexture();load(path); };
		Texture2DOpenGL(unsigned int width,unsigned int height, void * data = nullptr) : 
						width{ width }, 
						height{ height }, 
						channels{ 4 } {generateTexture(); setData(data);};

	private:
		unsigned int width, height;
		unsigned int channels;
		unsigned int textureID;

		void generateTexture();
	};



}


#endif