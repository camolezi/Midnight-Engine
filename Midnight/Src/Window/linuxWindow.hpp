#ifndef LINUXWINDOW
#define LINUXWINDOW

#include <window.hpp>


#include <glad.h>
#include <GLFW/glfw3.h>
	

namespace MN{

	//Window using GLFW and OpenGL
	//Change this class name to GLFW_Window
	class LinuxWindow : public Window{

		public:
			LinuxWindow(const WindowData& data);
			~LinuxWindow();	


			void setVSync(const bool vsy) override;
			bool getVSync() const override{return data.vsync;};

			void update() override;

			unsigned int getWidth() const override{return data.width;}
			unsigned int getHeight() const override{return data.height;}

			void* getNativeWindow() override;

		private:
			void initialize();

			WindowData data;
			//GLFWwindow
			GLFWwindow * glfwWindow;
			

	};

}


#endif 