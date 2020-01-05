#ifndef EVENT
#define EVENT

#include <string>
#include <memory>


namespace MN{

	//Define time here but change later
	using timeStamp = float;

	//Event interface
	class Event{

		public:

			//Check another solution later
			enum class EventType{
				message,
				WindowCloseEvent,
				WindowResizedEvent,
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



	//Message event, send a string message to another subsystem (used for tests(for now))
	class MessageEvent : public EventBase{

		public:

			MessageEvent( std::string message = "Empty message", timeStamp time = 0) : EventBase{time}, _message{message}{};

			EventType type() const override{
				return EventType::message;
			}

			std::string getName() const override{
				return "MessageEvent";
			}

			std::string getMessage() const {
				return _message;
			}

		private:

			std::string _message;
	};


	//Release the event pointer and convert to a specific child event pointer
	template <typename T>
	inline std::shared_ptr<T> downcast_event_ptr(Event::shared_ptr& ptr){
		//return std::move(std::unique_ptr<T>(std::move(static_cast<T*>(ptr.release()))) );

		//Maybe change to static_cast in release mode
		return std::dynamic_pointer_cast<T>(ptr);
	}


	//used to create new events
	template <typename Type, typename... Args> 
	inline std::unique_ptr<Event> newEvent(Args... var2) { 
	    return std::move( std::make_unique<Type>(var2...) );
	} 
  


}

#endif