#ifndef INPUTEVENT
#define INPUTEVENT
	
#include <event.hpp>
#include <key.hpp>

namespace MN{

	template<typename T>
	class PressableEvent : public EventBase{
		public:
			PressableEvent(T key,timeStamp time = 0) : EventBase{time} ,key{key}{};
			T getPressed(){ return key;}

		protected:
			T key;
	};


	class KeyPressedEvent : public PressableEvent<Key>{
		public:
			KeyPressedEvent(Key key,timeStamp time = 0) : PressableEvent{key,time}{};

			EventType type() const override{ return EventType::KeyPressedEvent; } 
			std::string getName() const override{ return "Key Pressed Event";}
	};


	class KeyReleasedEvent : public PressableEvent<Key>{
		public:
			KeyReleasedEvent(Key key,timeStamp time = 0) : PressableEvent{key,time}{};

			EventType type() const override{ return EventType::KeyReleasedEvent; } 
			std::string getName() const override{ return "Key Released Event";}
	};


	class MouseButtonPressedEvent : public PressableEvent<MouseButton>{
		public:
			MouseButtonPressedEvent(Key key,timeStamp time = 0) : PressableEvent{key,time}{};

			EventType type() const override{ return EventType::MouseButtonPressedEvent; } 
			std::string getName() const override{ return "Mouse Button Pressed Event";}
	};


	class MouseButtonReleasedEvent : public PressableEvent<MouseButton>{
		public:
			MouseButtonReleasedEvent(Key key,timeStamp time = 0) : PressableEvent{key,time}{};

			EventType type() const override{ return EventType::MouseButtonReleasedEvent; } 
			std::string getName() const override{ return "Mouse Button Released Event";}
	};


}





#endif