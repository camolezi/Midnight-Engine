#include <layer.hpp>
#include <debug.hpp>
#include <algorithm>


namespace MN {

	void LayerStack::addLayer(Layer::ptr layer){
		ASSERT(layer != nullptr, "Layer is a empty object");
		layer->onAttach();
		layers.push_back(layer);
	}
	void LayerStack::removeLayer(Layer::ptr layer){
		auto element = std::find(layers.begin(), layers.end(), layer);
		if (element != layers.end()) {
			layer->onDettach();
			layers.erase(element);
		}
		else {
			TERMINAL_LOG(Log::Warning, "Tried to delete a layer that does not exist: " << layer->getName());
		}
		
	}
	void LayerStack::clear()
	{
		for (auto element : layers) {
			element->onDettach();
		}

		layers.clear();
	}
}