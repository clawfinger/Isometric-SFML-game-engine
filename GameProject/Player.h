#pragma once
#include <SFML/Graphics.hpp>
#include <stack>
class Map;

class Player
{
public:
	void create(sf::Texture& texture);
	sf::Vector2f getPosition();
	void setPosition(const sf::Vector2f& position);
	sf::Sprite& getSprite();
	void setPath(std::stack<sf::Vector2f> path, int pathEnd);
	int getPathEnd();
	void move(const sf::Vector2f& movement);
	bool isPathSet();
	std::stack<sf::Vector2f>& getPath();

private:
	sf::Sprite m_sprite;
	sf::Vector2f m_position;
	std::stack<sf::Vector2f> m_currentPath;
	int m_pathEnd;
};
