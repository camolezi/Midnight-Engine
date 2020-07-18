#ifndef LAYER_HPP
#define LAYER_HPP

#include <vector>
#include <memory>
#include <string>

namespace MN {

	class Layer {
	public:
		using ptr = std::shared_ptr<Layer>;

		virtual ~Layer() = default;
		virtual void update(double deltaTime) = 0;
		virtual void start() = 0;

		virtual void onAttach() = 0;
		virtual void onDettach() = 0;

		virtual std::string getName() = 0;
	};


	class LayerStack {
	public:
		void addLayer(Layer::ptr layer);
		void removeLayer(Layer::ptr layer);

		void clear();
		
		std::vector<Layer::ptr>::iterator begin() { return layers.begin(); }
		std::vector<Layer::ptr>::iterator end() { return layers.end(); }
	private:
		std::vector<Layer::ptr> layers;
	};



}

#endif