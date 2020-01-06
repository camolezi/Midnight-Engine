#ifndef EVENTMACRO
#define EVENTMACRO

#include <eventDispatcher.hpp>
#include <event.hpp>
#include <inputEvent.hpp>
#include <windowEvent.hpp>
//Macros for facilitating using the event API

//Subscribe
#define EventSubscribe(type, function) \
	MN::EventDispatcher::dispatcher().subscribe(MN::Event::EventType::type,function);

//Dispatche
#define EventDispatche(event) \
	MN::EventDispatcher::dispatcher().queueEvent(event);


using MidnightEvent = MN::Event::pointer;  

#endif