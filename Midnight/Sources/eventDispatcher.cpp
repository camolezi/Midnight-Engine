#include <eventDispatcher.hpp>
#include <terminalLog.hpp>
#include <algorithm>

namespace MN{

	//Needs to check if the listener is alredy in the list( or map)
	void eventDispatcher::addListener(const Event::EventType type,memberPtr pointer){
		//Pointer not in the list case not working for now (std::function does not have a == operator)
		//auto test = std::find(callbacksMap[type].begin(), callbacksMap[type].end(), pointer);
		if(true){
			callbacksMap[type].push_back(pointer);	
		}
		//Pointer already in the queue
		else{
			TERMINAL_LOG(Log::Error, "Function already subscribed for type of event");
		}	
	}


	void eventDispatcher::fastEvent(Event::unique_ptr& event){
		for (auto& ptrAux : callbacksMap[event->type()]){
				//ptrAux(std::move(event));
		}
	}

	void eventDispatcher::queueEvent(Event::unique_ptr& event){
		eventQueue.push(std::move(event));
	}


	//Dispatche the next event of the queue
	void eventDispatcher::update(){
		if(!eventQueue.empty()){
			Event::shared_ptr sharedPointer = std::move(eventQueue.front());

			for (auto& ptrAux : callbacksMap[sharedPointer->type()]){
				ptrAux(sharedPointer);
			}

			eventQueue.pop();
		}
	}


}