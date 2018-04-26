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
	bool contains(const std::string& string) const;
	StringList& operator<<(const std::string& string);
	std::vector<std::string>::iterator begin();
	std::vector<std::string>::iterator end();
	std::vector<std::string>::const_iterator begin() const;
	std::vector<std::string>::const_iterator end() const;
private:
	std::vector<std::string> m_strings;
};