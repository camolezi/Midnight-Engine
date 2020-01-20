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


using MidnightEvent = MN::Event::pointer;  

#endif