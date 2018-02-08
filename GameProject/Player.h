#pragma once
#include <SFML/Graphics.hpp>

class Player
{
private:
	sf::Sprite m_sprite;
	sf::Vector2f m_position;
public:
	void create(sf::Texture& texture);
	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f position);
	sf::Sprite& getSprite();
};
