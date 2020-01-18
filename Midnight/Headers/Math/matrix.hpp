#ifndef MATH_MATRIX
#define MATH_MATRIX

#include <array>
#include <algorithm>
#include <string>

#include <vector.hpp>
#include <debug.hpp>

namespace MN{
	namespace Math{

		// square Matrix
		template<typename T , std::size_t N>
        class Matrix{
			public:
				T data[N][N];

				Matrix(){zero();}

				T at(const std::size_t index1,const std::size_t index2) const{
					ASSERT(index1 >= 0 && index1 < N,"Index of Matrix out of range: " << index1 << " " << index2);
					ASSERT(index2 >= 0 && index2 < N,"Index of Matrix out of range: " << index1 << " " << index2);
					
					return data[index1][index2];
				}

				void zero(){
					for(std::size_t x =0; x < N; x++){
						for(std::size_t y = 0; y < N; y++){
							data[x][y] = static_cast<T>(0);
						}
					}
				}

				//Identity matrix 
				void clear(){
					for(std::size_t x =0; x < N; x++){
						for(std::size_t y = 0; y < N; y++){
							if(x == y)
								data[x][y] = static_cast<T>(1);
							else
								data[x][y] = static_cast<T>(0);
						}
					}
				}

				std::string to_string(){
					std::string ret = "";
					for(std::size_t x =0; x < N; x++){
						for(std::size_t y = 0; y < N; y++){
							ret += std::to_string(data[x][y]) + " ";
						}
						ret += "\n";
					}
					return ret;
				}

				std::size_t size() const{
					return _size;
				}

				const void * getData() const{return data;}

			private:
				std::size_t _size = N;
		};

		//Operators

		//Add
		template<typename T , std::size_t N>
		Matrix<T,N> operator+(const Matrix<T,N>& mat1, const Matrix<T,N>& mat2){
			Matrix<T,N> ret;
			for(std::size_t x =0; x < N; x++){
				for(std::size_t y = 0; y < N; y++){
					ret.data[x][y] = mat1.at(x,y) + mat2.at(x,y);
				}
			}

			return ret;
		}

		//Sub
		template<typename T , std::size_t N>
		Matrix<T,N> operator-(const Matrix<T,N>& mat1, const Matrix<T,N>& mat2){
			Matrix<T,N> ret;
			for(std::size_t x =0; x < N; x++){
				for(std::size_t y = 0; y < N; y++){
					ret.data[x][y] = mat1.at(x,y) - mat2.at(x,y);
				}
			}

			return ret;
		}

			//Mult Matrix * Vector
		template<typename T , std::size_t N, typename V>
		Vector<V,N> operator*(const Matrix<T,N>& mat, const Vector<V,N>& vec){
			
			Vector<V,N> ret(0);

			for(std::size_t x =0; x < N; x++){
				for (std::size_t count = 0 ; count < N; count++){
					ret[x] += mat.at(x,count) * vec.at(count);
				}
			}			
			

			return ret;
		}


        //homogene coordenates multiplication
		template<typename T , std::size_t N, typename V>
		Vector<V,N-1> operator*(const Matrix<T,N>& mat, const Vector<V,N-1>& vec){
			
			Vector<V,N-1> ret(0);

			for(std::size_t x =0; x < N-1; x++){
				for (std::size_t count = 0 ; count < N; count++){
					if(count == N-1)
						ret[x] += mat.at(x,count) * 1;
					else
						ret[x] += mat.at(x,count) * vec.at(count);
                }
            }

			return ret;
		}



		//Inversion
		template<typename T , std::size_t N>
		Matrix<T,N> operator-(const Matrix<T,N>& mat){
			Matrix<T,N> ret;
			for(std::size_t x =0; x < N; x++){
				for(std::size_t y = 0; y < N; y++){
					ret.data[x][y] = -mat.at(x,y);
				}
			}

			return ret;
		}



		//Mult Matrix * Matrix
		template<typename T , std::size_t N>
		Matrix<T,N> operator*(const Matrix<T,N>& mat1, const Matrix<T,N>& mat2){
			Matrix<T,N> ret;

			for(std::size_t x =0; x < N; x++){
				for(std::size_t y = 0; y < N; y++){
					for (std::size_t count = 0 ; count < N; count++){
						ret.data[x][y] += mat1.at(x,count) * mat2.at(count,y);
					}
				}
			}			
			

			return ret;
		}


	}//End namespace math
}



#endif
