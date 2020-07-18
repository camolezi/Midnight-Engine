#ifndef WINDOWEVENT
#define WINDOWEVENT


#include <event.hpp>


namespace MN{

	class WindowCloseEvent : public EventBase{
		public:
			WindowCloseEvent(timeStamp time = 0) : EventBase{time}{};

			EventType type() const override{ return EventType::WindowCloseEvent; } 
			std::string getName() const override{ return "WindowCloseEvent";}
			std::string to_string() const override { return "Window Close Event";}
	};

	class WindowResizedEvent : public EventBase{
		public:
			WindowResizedEvent(unsigned int width,unsigned int height,timeStamp time = 0) : 
				EventBase{time}, 
				width{width}, 
				height{height}{};

			EventType type() const override{ return EventType::WindowResizedEvent; } 
			std::string getName() const override{ return "WindowResizedEvent";}
			std::string to_string() const override { 
				return "WindowResizedEvent: Width{" + std::to_string(width) + "} Height{" +  std::to_string(height) +"}";}

			unsigned int getWidth() const {return width;}
			unsigned int getHeight() const {return height;}

		private:
			unsigned int width, height;
	};

	class WindowMinimizedEvent : public EventBase{
		public:
			WindowMinimizedEvent(timeStamp time = 0) : EventBase{time}{};

			EventType type() const override{ return EventType::WindowMinimizedEvent; } 
			std::string getName() const override{ return "WindowMinimizedEvent";}
			std::string to_string() const override { return "Window Minimized Event";}
	};

	class WindowRestoredEvent : public EventBase{
		public:
			WindowRestoredEvent(timeStamp time = 0) : EventBase{time}{};

			EventType type() const override{ return EventType::WindowRestoredEvent; } 
			std::string getName() const override{ return "WindowRestoredEvent";}
			std::string to_string() const override { return "Window Restored Event";}
	};

		

}




#endif