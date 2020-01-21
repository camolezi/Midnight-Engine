#ifndef MATH_TRANSFORMATION
#define MATH_TRANSFORMATION

#include <math.h>
#include <matrix.hpp>
#include <vector.hpp>

//Pi just for testing 
#define PI 3.14

namespace MN{
	namespace Math{
		namespace Transformation3D{

			template<typename T>
			MN::Math::Matrix<T,4> translate(const MN::Math::Vector3<T>& tr){
				MN::Math::Matrix<T,4> ret;
				ret.clear();

				for(int x = 0; x < 3; x++){
        			ret.data[x][3] = tr.at(x);
			    }

				return ret;
			}


			
			template<typename T>
			MN::Math::Matrix<T,4> scale(const MN::Math::Vector3<T>& tr){
				MN::Math::Matrix<T,4> ret;
				ret.clear();

				 for(int x = 0; x < 3; x++){
        			ret.data[x][x] = tr.at(x);
			    }

				return ret;
			}

			
			
			template<typename T>
			MN::Math::Matrix<T,4> rotateZ(T angle){
				MN::Math::Matrix<T,4> ret;
				ret.clear();

                T cosO = static_cast<T>( cos( (angle * PI) / 180.0) );
                T senO = static_cast<T>(sin((angle * PI) / 180.0));

				
		    	ret.data[0][0] = cosO;
			    ret.data[1][0] = senO;
			    ret.data[0][1] = -senO;
			    ret.data[1][1] = cosO;

				return ret;
			}

			template<typename T>
			MN::Math::Matrix<T,4> rotateX(T angle){
				MN::Math::Matrix<T,4> ret;
				ret.clear();

                T cosO = cos( (angle * PI) / 180.0);
                T senO = sin((angle * PI) / 180.0);

				
		    	ret.data[1][1] = cosO;
			    ret.data[2][1] = senO;
			    ret.data[1][2] = -senO;
			    ret.data[2][2] = cosO;


				return ret;
			}

			template<typename T>
			MN::Math::Matrix<T,4> rotateY(T angle){
				MN::Math::Matrix<T,4> ret;
				ret.clear();

                T cosO = cos( (angle * PI) / 180.0);
                T senO = sin((angle * PI) / 180.0);
		    
			    ret.data[0][0] = cosO;
			    ret.data[2][0] = -senO;
			    ret.data[0][2] = senO;
			    ret.data[2][2] = cosO;

				return ret;
			}

			template<typename T>
			MN::Math::Matrix<T,4> rotate(const MN::Math::Vector3<T>& rt){
				MN::Math::Matrix<T,4> ret;

				ret = rotateZ(rt.at(2))*rotateY(rt.at(1))*rotateX(rt.at(0));

				return ret;
			}



			//Camera Matrix
			template<typename T>
			MN::Math::Matrix<T,4> orthographic(const T& left,
											   const T& right, 
											   const T& top,
											   const T& bottom,
											   const T& near,
											   const T& far)
			{
				MN::Math::Matrix<T,4> ret;

				ret.data[0][0] = static_cast<T>(2)/(right-left);
				ret.data[1][1] = static_cast<T>(2)/(top - bottom);
				ret.data[2][2] = static_cast<T>(-2)/(far-near);
				ret.data[0][3] = -(right + left)/(right - left);	
				ret.data[1][3] = -(top + bottom)/(top - bottom);
				ret.data[2][3] = -(far + near)/(far - near);
				ret.data[3][3] = static_cast<T>(1);

				return ret;
			}





		}//End of transformation3D

	}//End of namespace math
}


#endif
