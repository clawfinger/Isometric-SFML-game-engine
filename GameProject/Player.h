#pragma once
#include <SFML/Graphics.hpp>
#include <stack>
class Map;

class Player
{
public:
	void create(sf::Texture& texture);
	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f position);
	sf::Sprite& getSprite();
	void setPath(std::stack<sf::Vector2i> path, int pathEnd);
	sf::Vector2i getTargetTile();
	bool startMovement();
	int getPathEnd();

private:
	void setTargetTile(sf::Vector2i target);

private:
	sf::Sprite m_sprite;
	sf::Vector2f m_position;
	std::stack<sf::Vector2i> m_currentPath;
	sf::Vector2i m_targetTile;
	int m_pathEnd;
};
