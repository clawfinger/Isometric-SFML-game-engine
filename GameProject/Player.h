#pragma once
#include <SFML/Graphics.hpp>
#include "Actor.h"

//TODO: stub classes for battle engine creation simplification. Replace with actual classes asap!
class Player: public Actor
{
public:
	Player();
	virtual void update(sf::Time deltaTime);
};

class Enemy : public Actor
{
public:
	Enemy();
	virtual void update(sf::Time deltaTime);
};