#ifndef TEXTUREOPENGL_HPP
#define TEXTUREOPENGL_HPP

#include <texture.hpp>

namespace MN {

	class Texture2DOpenGL : public Texture2D {
	public:
		void bind() override;
		void load(const std::string& path) override;
		~Texture2DOpenGL();

		Texture2DOpenGL() : width{ 0 }, height{ 0 }, channels{ 0 } {generateTexture(); };
		Texture2DOpenGL(const std::string& path) { generateTexture();load(path); };

	private:
		unsigned int width, height;
		unsigned int channels;
		unsigned int textureID;

		void generateTexture();
	};



}


#endif