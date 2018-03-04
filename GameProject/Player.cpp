#include "stdafx.h"
#include "Player.h"
#include "utility.h"


Player::Player()
{
	m_playerSpeed = 200.0;
}

void Player::update(sf::Time deltaTime)
{
	if (isPathSet())
	{
		if (getPath().top() != getPosition())
		{
			sf::Vector2f playerMoveVector = getPath().top() - getPosition();
			sf::Vector2f normalazedVector = Vector::normalize<sf::Vector2f>(playerMoveVector);
			sf::Vector2f movement = normalazedVector * deltaTime.asSeconds() * m_playerSpeed;
			if (Vector::length<sf::Vector2f>(playerMoveVector) < Vector::length<sf::Vector2f>(movement))
			{
				setPosition(getPath().top());
				getPath().pop();
			}
			else
			{
				move(movement);
			}

		}
		else
			getPath().pop();
	}
}


