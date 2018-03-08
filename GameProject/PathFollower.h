#pragma once
#include <SFML/Graphics.hpp>
#include <stack>

class Actor;
class PathFollower
{
public:
	PathFollower();
	void setPath(std::stack<sf::Vector2f> path, int pathEnd);
	int getPathEnd();
	bool isPathSet();
	std::stack<sf::Vector2f>& getPath();
	void update(Actor& actor, sf::Time elapsed);

private:
	std::stack<sf::Vector2f> m_currentPath;
	int m_pathEnd;
};

