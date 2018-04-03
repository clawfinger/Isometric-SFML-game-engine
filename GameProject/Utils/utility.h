#pragma once
#include <SFML/System/Vector2.hpp>
#include <math.h>
#include <string>
#include <vector>

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


class StringList
{
public:
	StringList();
	bool contains(const std::string& string);
	StringList& operator<<(const std::string& string);
private:
	std::vector<std::string> m_strings;
};