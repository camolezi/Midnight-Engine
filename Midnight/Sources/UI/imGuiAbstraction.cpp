#include <imGuiAbstraction.hpp>
#include <imgui.h>

namespace MN {

	//std::unordered_map<Transform2D, bool> MidnightUI::_transforms;

	void MidnightUI::showWidget(Transform2D& transform, vec4& color){

		static bool win = true;
		ImGui::Begin("Transform 2D", &win);
		ImGui::DragFloat2("Position", transform.Position.getData());
		ImGui::DragFloat("Rotation", &transform.Rotation);
		ImGui::DragFloat2("Scale", transform.Scale.getData());
		ImGui::ColorEdit4("Color", color.getData());
		ImGui::DragFloat("Depth", &transform.Position.z() );
		ImGui::End();
		
		//		ImGui::ShowTestWindow()


	}

	void MidnightUI::showWidget(Transform2D& transform){

		static bool win = true;
		ImGui::Begin("Transform 2D", &win);
		ImGui::DragFloat2("Position", transform.Position.getData());
		ImGui::DragFloat("Rotation", &transform.Rotation);
		ImGui::DragFloat2("Scale", transform.Scale.getData());
		ImGui::DragFloat("Depth", &transform.Position.z());
		ImGui::End();
	}

}