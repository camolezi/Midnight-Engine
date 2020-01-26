#ifndef IMGUIABSTRACTION_HPP
#define IMGUIABSTRACTION_HPP

#include <imgui.h>
#include <transform.hpp>
#include <unordered_map>

//Some abstraction for displaying imgui graphics with easy,use while the interface is not yet ready

//Macros for using
#ifdef deploy
	#define MidnightWidget(...)
#else
	#define MidnightWidget(...) \
			MN::MidnightUI::showWidget(__VA_ARGS__)
#endif

namespace MN{

	class MidnightUI {
	public:

		static void showWidget(Transform2D& transform, vec4& color);
		static void showWidget(Transform2D& transform);

	private:
		//static std::unordered_map<Transform2D,bool> _transforms;
	};


}




#endif