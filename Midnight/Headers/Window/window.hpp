#ifndef WINDOW
#define WINDOW

#include <string>
#include <memory>
	
namespace MN{

	class WindowData{
		public:
			unsigned int width;
			unsigned int height;
			std::string title;
			bool vsync;

			WindowData(unsigned int width = 1280,
					   unsigned int height = 720,
					   std::string title = "Midnight Engine",
					   bool vsync = false):
					   		width{width}, 
					   		height{height},
					   		title{title},
					   		vsync{vsync}{};
	};


	//Interface for desktop window
	class Window{

		public:

			using pointer = std::unique_ptr<Window>;

			virtual ~Window(){};
			virtual void update() = 0;

			virtual void setVSync(const bool vsy) =0;
			virtual bool getVSync() const = 0;

			virtual unsigned int getWidth() const = 0;
			virtual unsigned int getHeight() const = 0;	

			static pointer create(const WindowData& data = WindowData());

	};

}		
	
	

#endif