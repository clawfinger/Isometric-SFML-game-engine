#pragma once
#include <SFML/Graphics.hpp>
#include "PathFollower.h"
#include "Entity.h"

class Map;

class Player: public Entity, public PathFollower
{
public:
	Player();
	void update(sf::Time deltaTime);

private:
	float m_playerSpeed;
};
