#ifndef INPUT_HPP
#define INPUT_HPP

#include <unordered_map>
#include <key.hpp>
#include <mouseButton.hpp>

namespace MN{

	//Plataform Independent input class
	//Uses Midnight event system to verify the input status
	class Input{
	public:
		
		static bool isKeyPressed (Key code);
		static bool isMousePressed (MouseButton code);

		static PixelType getMouseX(){return mouseX;};
		static PixelType getMouseY(){return mouseY;};

		static void start();


	private:
		Input();
		static std::unordered_map<Key,bool> keyStatus;

		static PixelType mouseX;
		static PixelType mouseY;
	};
}




#endif