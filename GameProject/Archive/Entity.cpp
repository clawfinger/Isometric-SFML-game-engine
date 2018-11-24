#include "Entity.h"

void Entity::create(sf::Texture & texture)
{
	m_sprite.setTexture(texture);
}

sf::Vector2f Entity::getPosition()
{
	return m_position;
}

void Entity::setPosition(const sf::Vector2f& position)
{
	m_position = position;
	m_sprite.setPosition(position.x, position.y);
}

sf::Sprite & Entity::getSprite()
{
	return m_sprite;
}



void Entity::move(const sf::Vector2f & movement)
{
	m_position += movement;
	m_sprite.move(movement.x, movement.y);
}