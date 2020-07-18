#ifndef CAMERA_H
#define CAMERA_H

#include <coreMath.hpp>
#include <memory>

namespace MN{

	//ROtaion as vec3 for now

	class Camera{
	public:

		virtual void setPosition(const vec3& pos) = 0;
		virtual const vec3& getPosition() const =0;
		//virtual void setRotation(const vec3& rot) =0;

		virtual ~Camera(){}

		virtual	const mat4& viewProjMatrix() const = 0;
		virtual const mat4& projMatrix() const =0;
		virtual const mat4& viewMatrix() const =0;

		static std::shared_ptr<Camera> createOrthographic(float left, float right, float top, float bottom, float near, float far);
	};


	class OrthographicCamera : public Camera{
	public:
		
		OrthographicCamera(float left, float right, float top, float bottom, float near, float far);

		void setPosition(const vec3& pos) override;
		const vec3& getPosition() const override{return position;}

		const mat4& viewProjMatrix() const override{return _viewProjMatrix;}
		const mat4& projMatrix() const override{ return _projMatrix;}
		const mat4& viewMatrix() const override{ return _viewMatrix;}
	private:

		void calculateViewMatrix();

		vec3 position;

		mat4 _viewMatrix;
		mat4 _projMatrix;
		mat4 _viewProjMatrix;
	};

}


#endif