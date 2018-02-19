#pragma once
#include <SFML/System/Vector2.hpp>
#include <math.h>

namespace Vector
{
	template<typename T>
	float length(const T& vector)
	{
		return sqrt(pow(vector.x, 2) + pow(vector.y, 2));
	}

	template<typename T>
	T normalize(const T& vector)
	{
		return vector / length<T>(vector);
	}
}
