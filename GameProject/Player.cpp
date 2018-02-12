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

void Player::setPath(std::stack<sf::Vector2i> path, int pathEnd)
{
	m_currentPath = path;
	m_pathEnd = pathEnd;
}

void Player::setTargetTile(sf::Vector2i target)
{
	m_targetTile = target;
}

sf::Vector2i Player::getTargetTile()
{
	return m_targetTile;
}

bool Player::startMovement()
{
	if (m_currentPath.empty())
		return false;
	else
	{
		m_targetTile = m_currentPath.top();
		m_currentPath.pop();
		return true;
	}
}

int Player::getPathEnd()
{
	return m_pathEnd;
}


