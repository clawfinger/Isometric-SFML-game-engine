#pragma once
#include <SFML/System/Vector2.hpp>
#include <math.h>
#include <string>
#include <vector>
#include <random>

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

	bool isVectorsIntersects(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c, sf::Vector2f d);
}

template<typename T>
T getRandomInRange(T a, T b)
{
	std::random_device rd;     
	std::mt19937 rng(rd());    
	std::uniform_int_distribution<T> uni(a, b);
	return uni(rng);
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

struct Point
{
	int x;
	int y;
};