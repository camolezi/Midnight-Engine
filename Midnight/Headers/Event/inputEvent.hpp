#ifndef INPUTEVENT
#define INPUTEVENT
	
#include <event.hpp>
#include <key.hpp>

namespace MN{


	class KeyEvent : public EventBase{
		public:
			KeyEvent(Key key,timeStamp time = 0) : EventBase{time} ,key{key}{};

			Key getKey(){ return key;}

		protected:
			Key key;
	};


	class KeyPressedEvent : public KeyEvent{
		public:
			KeyPressedEvent(Key key,timeStamp time = 0) : KeyEvent{key,time}{};

			EventType type() const override{ return EventType::KeyPressedEvent; } 
			std::string getName() const override{ return "Key Pressed Event";}
	};


	class KeyReleasedEvent : public KeyEvent{
		public:
			KeyReleasedEvent(Key key,timeStamp time = 0) : KeyEvent{key,time}{};

			EventType type() const override{ return EventType::KeyReleasedEvent; } 
			std::string getName() const override{ return "Key Released Event";}
	};



}





#endif