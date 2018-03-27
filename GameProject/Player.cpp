#include "stdafx.h"
#include "Player.h"

Player::Player(): Actor()
{
}

void Player::update(sf::Time deltaTime)
{
	Actor::pathComponent().update(*this, deltaTime);
}

Enemy::Enemy() : Actor()
{
}

void Enemy::update(sf::Time deltaTime)
{
	Actor::pathComponent().update(*this, deltaTime);
}