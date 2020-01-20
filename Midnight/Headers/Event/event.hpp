#ifndef EVENT
#define EVENT

#include <string>
#include <memory>
#include <debug.hpp>

namespace MN{

	//Define time here but change later
	using timeStamp = float;

	//Event interface
	class Event{

		public:

			//Check another solution later
			enum class EventType{
				WindowCloseEvent,
				WindowResizedEvent,
				MouseMovedEvent,
				KeyPressedEvent,
				KeyReleasedEvent,
				MouseButtonPressedEvent,
				MouseButtonReleasedEvent
			};

			using unique_ptr = std::unique_ptr<Event>;
			using shared_ptr = std::shared_ptr<Event>;

			//Definition for use in definition of callbacks functions
			using pointer = std::shared_ptr<Event>&;

			virtual ~Event(){};

			virtual EventType type() const = 0; 
			virtual timeStamp getTimeStamp() const = 0;
			virtual std::string getName() const = 0;
			virtual std::string to_string() const = 0;

		private:

	};

	//Base Event class
	class EventBase : public Event{

		public:

			virtual ~EventBase(){}
			virtual timeStamp getTimeStamp() const override{
				return _eventTime;
			}


		protected:
			EventBase(timeStamp eventTime) : _eventTime{eventTime}{}

		private:
			timeStamp _eventTime;
	};

	//Release the event pointer and convert to a specific child event pointer
	template <typename T>
	inline std::shared_ptr<T> downcast_event_ptr(Event::shared_ptr& ptr){
		//return std::move(std::unique_ptr<T>(std::move(static_cast<T*>(ptr.release()))) );

		//Maybe change to static_cast in release mode
		auto ret= std::dynamic_pointer_cast<T>(ptr);
		ASSERT(ret,"Down Cast Event Error");
		return ret;
	}


	//used to create new events
	template <typename Type, typename... Args> 
	inline std::unique_ptr<Event> newEvent(Args... var2) { 
	    return std::move( std::make_unique<Type>(var2...) );
	} 
  


}

#endif