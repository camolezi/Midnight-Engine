#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include <coreMath.hpp>

namespace MN{
	
	//3d Transform, not used for now
	class Transform{
	public:
		vec3 Position;
		vec3 Rotation;
		vec3 Scale; 
	};

	class Transform2D{
	public:
		Transform2D(const vec3& Position = { 0,0,0 }, float Rotation = 0, const vec2& Scale = {1,1}) :
					Position{Position},Rotation{Rotation},Scale{Scale}{};

		vec3 Position;
		float Rotation;
		vec2 Scale;

		mat4 modelMatrix() const{
			return transformation3D::translate(Position) * 
				   transformation3D::rotateZ(Rotation) *
				   transformation3D::scale(vec3{Scale.at(0),Scale.at(1),0.0f});
		}
	};
}

#endif