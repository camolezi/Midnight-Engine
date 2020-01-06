#ifndef MATH_VECTOR
#define MATH_VECTOR

#include <array>
#include <algorithm>
#include <debug.hpp>

						  
namespace MN{							
	namespace Math{

		template<typename T, std::size_t N>
		class Vector{
			public:
				//Constructors
                Vector(){}

				Vector(const T& init){
					std::fill(data.begin(),data.end(),init);
				}

				T& operator[](const std::size_t index){
					//Debug only
					//assert(index >= 0 && index < N);
					return data[index];
				}

				T at(const std::size_t index) const{
					//Debug only
					//assert(index >= 0 && index < N);
					return data[index];
				}


			protected:
				std::array<T,N> data;
		
		};


		template<typename T>
		class Vector2 : public Vector<T,2>{
			public:
				using Vector<T,2>::Vector;

				Vector2(const T& x, const T& y){
					this->data[0] = x;
					this->data[1] = y;
				}	

				Vector2(const Vector<T,2> vec){
					this->data[0] = vec.at(0);
					this->data[1] = vec.at(1);
				}

                T& x(){return this->data[0];}
                T& y(){return this->data[1];}

			private:
				
		};


		template<typename T>
		class Vector3 : public Vector<T,3>{
			public:
				using Vector<T,3>::Vector;

				Vector3(const T& x, const T& y, const T& z){
					this->data[0] = x;
					this->data[1] = y;
					this->data[2] = z;
				}	

				Vector3(const Vector<T,3> vec){
					this->data[0] = vec.at(0);
					this->data[1] = vec.at(1);
					this->data[2] = vec.at(2);
				}

                T& x(){return this->data[0];}
                T& y(){return this->data[1];}
                T& z(){return this->data[2];}

			private:
				
		};

		//Operations

		// add
		template<typename T, std::size_t N>
		Vector<T,N> operator+(const Vector<T,N>& vec1,const Vector<T,N>& vec2){
			Vector<T,N> ret;
			for(std::size_t it = 0; it < N; it++)
				ret[it] = vec1.at(it) + vec2.at(it);

			return ret;
		}


		// subtration
		template<typename T, std::size_t N>
		Vector<T,N> operator-(const Vector<T,N>& vec1,const Vector<T,N>& vec2){
			Vector<T,N> ret;
			for(std::size_t it = 0; it < N; it++)
				ret[it] = vec1.at(it) - vec2.at(it);

			return ret;
		}

		// multiplication member per member
		template<typename T, std::size_t N>
		Vector<T,N> operator*(const Vector<T,N>& vec1,const Vector<T,N>& vec2){
			Vector<T,N> ret;
			for(std::size_t it = 0; it < N; it++)
				ret[it] = vec1.at(it) * vec2.at(it);

			return ret;
		}	

		//Scalar multiplication
		template<typename T, std::size_t N, typename S>
		Vector<T,N> operator*(const Vector<T,N>& vec1,S scalar){
			Vector<T,N> ret;
			for(std::size_t it = 0; it < N; it++)
				ret[it] = vec1.at(it) * scalar;

			return ret;
		}

		template<typename T, std::size_t N, typename S>
		Vector<T,N> operator*(S scalar,const Vector<T,N>& vec2){
			Vector<T,N> ret;
			for(std::size_t it = 0; it < N; it++)
				ret[it] = scalar * vec2.at(it);

			return ret;
		}		

		// division member 
		template<typename T, std::size_t N>
		Vector<T,N> operator/(const Vector<T,N>& vec1,const Vector<T,N>& vec2){
			Vector<T,N> ret;
			for(std::size_t it = 0; it < N; it++)
				ret[it] = vec1.at(it) / vec2.at(it);

			return ret;
		}

		//Division Scalar
		template<typename T, std::size_t N, typename S>
		Vector<T,N> operator/(const Vector<T,N>& vec1,S scalar){
			Vector<T,N> ret;
			for(std::size_t it = 0; it < N; it++)
				ret[it] = vec1.at(it) / scalar;

			return ret;
		}

		template<typename T, std::size_t N,typename S>
		Vector<T,N> operator/(S scalar,const Vector<T,N>& vec2){
			Vector<T,N> ret;
			for(std::size_t it = 0; it < N; it++)
				ret[it] = scalar / vec2.at(it);

			return ret;
		}


		//Inversion
		template<typename T, std::size_t N>
		Vector<T,N> operator-(const Vector<T,N>& vec){
			Vector<T,N> ret;
			for(std::size_t it = 0; it < N; it++)
				ret[it] = -vec.at(it);

			return ret;
		}


	}//End Namespace Math
}


#endif 
