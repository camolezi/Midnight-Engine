#ifndef INPUTEVENT
#define INPUTEVENT
	
#include <event.hpp>
#include <key.hpp>
#include <mouseButton.hpp>

namespace MN{


	//Mouse cursor event
	class MouseMovedEvent : public EventBase{		
		public:
			MouseMovedEvent(PixelType xPos, PixelType yPos,timeStamp time = 0) : 
				EventBase{time},
				xPos{xPos},
				yPos{yPos} {};

			EventType type() const override{ return EventType::MouseMovedEvent; } 
			std::string getName() const override{ return "MouseMovedEvent";}

			std::string to_string() const override { 
				return "MouseMovedEvent: XPOS{" + std::to_string(xPos) + "} YPOS{" +  std::to_string(yPos) +"}";}

			PixelType getX() const{return xPos;}
			PixelType getY() const{return yPos;}
		private:
			PixelType xPos,yPos;
	};


	//Template class for pressable events, used for key events and mouse button events
	template<typename T>
	class PressableEvent : public EventBase{
		public:
			PressableEvent(T key,timeStamp time = 0) : EventBase{time} ,key{key}{};
			T pressed(){ return key;}

		protected:
			T key;
	};


	class KeyPressedEvent : public PressableEvent<Key>{
		public:
			KeyPressedEvent(Key key,timeStamp time = 0) : PressableEvent{key,time}{};

			EventType type() const override{ return EventType::KeyPressedEvent; } 
			std::string getName() const override{ return "KeyPressedEvent";}

			std::string to_string() const override { 
				return "KeyPressedEvent: Key{" + std::to_string(key) + "}";}
	};


	class KeyReleasedEvent : public PressableEvent<Key>{
		public:
			KeyReleasedEvent(Key key,timeStamp time = 0) : PressableEvent{key,time}{};

			EventType type() const override{ return EventType::KeyReleasedEvent; } 
			std::string getName() const override{ return "KeyReleasedEvent";}

			std::string to_string() const override { 
				return "KeyReleasedEvent: Key{" + std::to_string(key) + "}";}
	};


	class MouseButtonPressedEvent : public PressableEvent<MouseButton>{
		public:
			MouseButtonPressedEvent(Key key,timeStamp time = 0) : PressableEvent{key,time}{};

			EventType type() const override{ return EventType::MouseButtonPressedEvent; } 
			std::string getName() const override{ return "MouseButtonPressedEvent";}

			std::string to_string() const override { 
				return "MouseButtonPressedEvent: Button{" + std::to_string(key) + "}";}
	};


	class MouseButtonReleasedEvent : public PressableEvent<MouseButton>{
		public:
			MouseButtonReleasedEvent(Key key,timeStamp time = 0) : PressableEvent{key,time}{};

			EventType type() const override{ return EventType::MouseButtonReleasedEvent; } 
			std::string getName() const override{ return "Mouse Button Released Event";}

			std::string to_string() const override { 
				return "MouseButtonReleasedEvent: Button{" + std::to_string(key) + "}";}
	};


}





#endif