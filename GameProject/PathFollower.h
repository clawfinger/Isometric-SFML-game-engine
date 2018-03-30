#pragma once
#include <SFML/Graphics.hpp>
#include <stack>

class Actor;
class PathFollower
{
public:
	PathFollower(Actor* actor);
	void setPath(std::stack<sf::Vector2f> path, int pathEnd);
	int getPathEnd();
	bool isPathSet();
	std::stack<sf::Vector2f>& getPath();
	void update(sf::Time elapsed);

private:
	std::stack<sf::Vector2f> m_currentPath;
	int m_pathEnd;
	Actor* m_actor;
};

