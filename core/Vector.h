/*!
\file
\brief base class that represents 2d point
\author Maganer
\version 0.1
\date 02.09.2023
*/


#ifndef VECTOR_H
#define VECTOR_H
namespace Goat2d
{
namespace core
{

	/*!
	\brief Template class to represent algebraic 2d vector.
	\author MAGANER
	\date 10.09.2023
	*/
	template<typename T>
	struct Vector2
	{
		T x, y;

		//! create vector with default value of its type
		Vector2()
		{
			x = T();
			y = T();
		}

		//! create vector with provided values
		Vector2(T x, T y):x(x),y(y){}

		//! copy constructor
		Vector2(const Vector2& vec)
		{
			this->x = vec.x;
			this->y = vec.y;
		}

		//! default = operator
		constexpr Vector2& operator=(const Vector2& vec) = default;

		//! add 2 vectors and return new vector
		constexpr Vector2 operator+(const Vector2& vec)
		{
			return Vector2(x + vec.x, y + vec.y);
		}

		//! substract 2 vectors and return new vector
		constexpr Vector2 operator-(const Vector2& vec)
		{
			return Vector2(x - vec.x, y - vec.y);
		}

		//! multiply vector by number and return new vector
		constexpr Vector2 operator*(T number)
		{
			return Vector2(x * number, y * number);
		}
		~Vector2(){}
	};

	//! compares two vectors and returns True if there are the same, else False
	template<class T>
	constexpr bool operator==(const Vector2<T>& a, const Vector2<T>& b)
	{
		return a.x == b.x and a.y == b.y;
	}


	//! vector that is based on integers
	typedef Vector2<int> Vector2i;

	//! vector that is based on float numbers
	typedef Vector2<float> Vector2f;
};
};
#endif