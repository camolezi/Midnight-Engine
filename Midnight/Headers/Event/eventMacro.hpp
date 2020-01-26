#ifndef EVENTMACRO
#define EVENTMACRO

#include <eventDispatcher.hpp>
#include <event.hpp>
#include <windowEvent.hpp>
#include <inputEvent.hpp>

//Macros for facilitating using the event API

//Subscribe
#define EventSubscribe(type, function) \
	MN::EventDispatcher::dispatcher().subscribe(MN::Event::EventType::type,function);

//Dispatche
#define EventDispatche(event) \
	MN::EventDispatcher::dispatcher().queueEvent(event);


#define KeyPressedSubscribe(function) \
	MN::EventDispatcher::dispatcher().subscribe(MN::Event::EventType::KeyPressedEvent, function);


//------------------- to be used by client application -----------------------------------------

//Subscribe for input Key (most used)
#define SubscribeKeyPress(key, function) \
	KeyPressedSubscribe([](MidnightEvent event) { \
		auto pressEvent = downcast_event_ptr<KeyPressedEvent>(event); \
		if (pressEvent->pressed() == key) { \
			function(); \
		} \
	}); \

//Subscribe for mouse right button
#define SubscribeRightMouseClick(function) \
	EventSubscribe(MouseButtonPressedEvent, [](MidnightEvent event) {   \
		auto pressEvent = downcast_event_ptr<MouseButtonPressedEvent>(event); \
		if (pressEvent->pressed() == MN_MOUSE_BUTTON_1) { \
			function(); \
		} \
	}); \

//Subscribe for mouse left button
#define SubscribeLeftMouseClick(function) \
	EventSubscribe(MouseButtonPressedEvent, [](MidnightEvent event) {   \
		auto pressEvent = downcast_event_ptr<MouseButtonPressedEvent>(event); \
		if (pressEvent->pressed() == MN_MOUSE_BUTTON_2) { \
			function(); \
		} \
	}); \



using MidnightEvent = MN::Event::pointer;  

#endif