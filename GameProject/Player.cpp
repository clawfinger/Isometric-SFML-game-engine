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

void Player::setPosition(const sf::Vector2f& position)
{
	m_position = position;
	m_sprite.setPosition(position.x, position.y);
}

sf::Sprite & Player::getSprite()
{
	return m_sprite;
}

void Player::setPath(std::stack<sf::Vector2f> path, int pathEnd)
{
	m_currentPath = path;
	m_pathEnd = pathEnd;
}

int Player::getPathEnd()
{
	return m_pathEnd;
}

void Player::move(const sf::Vector2f & movement)
{
	m_position += movement;
	m_sprite.move(movement.x, movement.y);
}

bool Player::isPathSet()
{
	return !m_currentPath.empty();
}

std::stack<sf::Vector2f>& Player::getPath()
{
	return m_currentPath;
}


