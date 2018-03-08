#pragma once
#include <SFML/Graphics.hpp>
#include "PathFollower.h"
#include "Actor.h"

class Map;

class Player: public Actor
{
public:
	Player();
	virtual void update(sf::Time deltaTime);
};
