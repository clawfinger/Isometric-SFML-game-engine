#pragma once
#include <SFML/Graphics.hpp>
#include "Actor.h"

class Player: public Actor
{
public:
	Player();
	virtual void update(sf::Time deltaTime);
};
