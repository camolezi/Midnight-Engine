#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>
#include <memory>

namespace MN {
	//Basic texture class
	class Texture {
	public:
		virtual ~Texture() = default;

		virtual void bind() = 0;
		virtual void load(const std::string& path) = 0;
		virtual void setData(void * data) = 0;
	};

	class Texture2D : public Texture {
	public:
		virtual ~Texture2D() = default;
		virtual void setSize(unsigned int width, unsigned int height) = 0;

		static std::unique_ptr<Texture2D> create(const std::string& path);
		static std::unique_ptr<Texture2D> create(unsigned int widht,unsigned int height, unsigned char* data);
		static std::unique_ptr<Texture2D> create();

	};
}


#endif