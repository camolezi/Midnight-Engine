#ifndef WINDOWEVENT
#define WINDOWEVENT


#include "event.hpp"


namespace MN{

	class WindowCloseEvent : public EventBase{
		public:
			WindowCloseEvent(timeStamp time = 0) : EventBase{time}{};

			EventType type() const override{ return EventType::WindowCloseEvent; } 
			std::string getName() const override{ return "WindowCloseEvent";}
	};

	class WindowResizedEvent : public EventBase{
		public:
			WindowResizedEvent(unsigned int width,unsigned int height,timeStamp time = 0) : 
				EventBase{time}, 
				width{width}, 
				height{height}{};

			EventType type() const override{ return EventType::WindowResizedEvent; } 
			std::string getName() const override{ return "WindowResizedEvent";}

			unsigned int getWidth() const {return width;}
			unsigned int getHeight() const {return height;}

		private:
			unsigned int width, height;
	};
		

}




#endif