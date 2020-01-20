#include <camera.hpp>

namespace MN{

	void OrthographicCamera::setPosition(const vec3& pos){
		position = pos;
		calculateViewMatrix();
	}


	void OrthographicCamera::calculateViewMatrix(){
		_viewMatrix = transformation3D::translate(vec3{-position});
		_viewProjMatrix = _projMatrix * _viewMatrix;
	}
	
	OrthographicCamera::OrthographicCamera(float left, float right, float top, float bottom, float near, float far){
		_projMatrix = transformation3D::orthographic(left,right,top,bottom,near,far);
		position = vec3{0,0,5.0f};
		calculateViewMatrix();

		_viewProjMatrix = _projMatrix * _viewMatrix;

		// TERMINAL_DEBUG(_projMatrix.to_string());
		// TERMINAL_DEBUG(_viewMatrix.to_string());
		// TERMINAL_DEBUG(_viewProjMatrix.to_string());
	}
}
