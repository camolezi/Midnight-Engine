#include <input.hpp>
#include <eventMacro.hpp>

namespace MN{

	//Static variable init
	std::unordered_map<Key,bool> Input::keyStatus;

	void Input::start(){

		//Subscribe to key pressed and released events to update the KeyStatus map
		EventSubscribe(KeyPressedEvent,[](MidnightEvent event){
			auto pressEvent = downcast_event_ptr<KeyPressedEvent>(event);
			keyStatus[pressEvent->pressed()] = true;
		});
		

		EventSubscribe(KeyReleasedEvent,[](MidnightEvent event){
			auto pressEvent = downcast_event_ptr<KeyReleasedEvent>(event);
			keyStatus[pressEvent->pressed()] = false;
		});


		//Mouse Events
		EventSubscribe(MouseButtonPressedEvent,[](MidnightEvent event){
			auto pressEvent = downcast_event_ptr<MouseButtonPressedEvent>(event);
			keyStatus[pressEvent->pressed()] = true;
		});
		

		EventSubscribe(MouseButtonReleasedEvent,[](MidnightEvent event){
			auto pressEvent = downcast_event_ptr<MouseButtonReleasedEvent>(event);
			keyStatus[pressEvent->pressed()] = false;
		});
		
	}

	bool Input::isKeyPressed(Key code){
		auto keyIt= keyStatus.find(code);
		if( keyIt == keyStatus.end()){
			return false;
		}else{
			return keyIt->second;
		}
	}

	bool Input::isMousePressed(MouseButton code){
		return isKeyPressed(code);
	}

}