#include "stdafx.h"
#include "Player.h"
#include "PathFollower.h"

Player::Player(): Actor()
{
}

void Player::update(sf::Time deltaTime)
{
	Actor::pathComponent()->update(deltaTime);
}

Enemy::Enemy() : Actor()
{
}

void Enemy::update(sf::Time deltaTime)
{
	Actor::pathComponent()->update(deltaTime);
}