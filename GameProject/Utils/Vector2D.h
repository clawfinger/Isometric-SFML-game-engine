#pragma once
#include <limits>

template <typename T>
class Vector2D final
{
public:
	explicit Vector2D(T _x = 0, T _y = 0) : x(_x), y(_y) {}

public:
	T x;
	T y;
};

//template <typename T>
//Vector2<T>& operator +=(Vector2<T>& left, const Vector2<T>& right);

template<typename T>
Vector2D<T> operator+(const Vector2D<T>& left, const Vector2D<T>& right)
{
	Vector2D<T> result;
	result.x = left.x + right.x;
	result.y = left.y + right.y;
	return result;
}

template<typename T>
Vector2D<T> operator-(const Vector2D<T>& left, const Vector2D<T>& right)
{
	Vector2D<T> result;
	result.x = left.x - right.x;
	result.y = left.y - right.y;
	return result;
}

template<typename T>
bool operator==(const Vector2D<T>& left, const Vector2D<T>& right)
{
	return left.x == right.x &&
		left.x == right.x;
}

template<typename T>
bool operator!=(const Vector2D<T>& left, const Vector2D<T>& right)
{
	return left.x != right.x ||
		left.x != right.x;
}

template<typename T>
Vector2D<T> operator/(const Vector2D<T>& left, T value)
{
	Vector2D<T> result;
	result.x = left.x / value;
	result.y = left.y / value;
	return result;
}

template<typename T>
Vector2D<T> operator*(const Vector2D<T>& left, T value)
{
	Vector2D<T> result;
	result.x = left.x * value;
	result.y = left.y * value;
	return result;
}

template<typename T>
Vector2D<T> operator*(T value, const Vector2D<T>& left)
{
	Vector2D<T> result;
	result.x = left.x * value;
	result.y = left.y * value;
	return result;
}

//probably better way to compare floats
//template<>
//bool operator==<float>(const Vector2D<T>& left, const Vector2D<T>& right)
//{
//	return (std::abs(left.x – right.x) <= std::numeric_limits<float>::epsilon() * std::max(1.0f, std::abs(left.x), std::abs(right.x)) &&
//			(std::abs(left.y – right.y) <= std::numeric_limits<float>::epsilon() * std::max(1.0f, std::abs(left.y), std::abs(right.y)) &&
//}
typedef Vector2D<int> Vector2i;
typedef Vector2D<float> Vector2f;
