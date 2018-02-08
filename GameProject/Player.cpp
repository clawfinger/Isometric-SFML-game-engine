#include "stdafx.h"
#include "Player.h"

void Player::create(sf::Texture & texture)
{
	m_sprite.setTexture(texture);
}

sf::Vector2f Player::getPosition()
{
	return m_position;
}

void Player::setPosition(sf::Vector2f position)
{
	m_position = position;
	m_sprite.setPosition(position);
}

sf::Sprite & Player::getSprite()
{
	return m_sprite;
}
