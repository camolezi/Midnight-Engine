#ifndef LAYER_HPP
#define LAYER_HPP


namespace MN {

	class Layer {
	public:

		virtual void update() = 0;
		virtual void start() = 0;

		virtual void onAttach() = 0;
		virtual void onDettach() = 0;
	};



}

#endif