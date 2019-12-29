#include <eventDispatcher.hpp>

namespace MN{
	//Needs to check if the listener is alredy in the list( or map)
	void eventDispatcher::addListener(memberPtr pointer){
		callbacks.push_back(pointer);
	}

	void eventDispatcher::fastEvent(Event::ptr& event){
		for (auto& ptrAux : callbacks){
			ptrAux(std::move(event));
		}
	}

	void eventDispatcher::queueEvent(Event::ptr& event){
		eventQueue.push(std::move(event));
	}


	//Dispatche one event of de queue for now
	void eventDispatcher::update(){
		if(!eventQueue.empty()){
			for (auto& ptrAux : callbacks){
				ptrAux(std::move(eventQueue.front()));
			}
			eventQueue.pop();
		}
	}

}