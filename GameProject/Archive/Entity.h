#pragma once
#include <SFML/Graphics.hpp>


class Entity
{
public:
	virtual void create(sf::Texture& texture);
	virtual sf::Sprite& getSprite();

	sf::Vector2f getPosition();
	void setPosition(const sf::Vector2f& position);

	virtual void move(const sf::Vector2f& movement);
	virtual void update(sf::Time deltaTime) = 0;
	virtual ~Entity() {};

protected:
	sf::Sprite m_sprite;
	sf::Vector2f m_position;
};
