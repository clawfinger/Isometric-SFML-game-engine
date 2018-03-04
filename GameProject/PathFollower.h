#pragma once
#include <SFML/Graphics.hpp>
#include <stack>

class PathFollower
{
public:
	void setPath(std::stack<sf::Vector2f> path, int pathEnd);
	int getPathEnd();
	bool isPathSet();
	std::stack<sf::Vector2f>& getPath();
	virtual ~PathFollower() {};

protected:
	std::stack<sf::Vector2f> m_currentPath;
	int m_pathEnd;
};

