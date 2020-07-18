#ifndef UILAYER_HPP
#define UILAYER_HPP

#include <layer.hpp>

namespace MN {


	//For now this layer will contein iamGui code
	class UILayer : public Layer {
	public:

		void update(double deltaTime) override;
		void start() override;

		void onAttach() override;
		void onDettach() override;

		~UILayer();

		std::string getName() override { return "UILayer"; }

	};

}


#endif