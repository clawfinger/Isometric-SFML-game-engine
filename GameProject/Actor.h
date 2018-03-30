#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"

class PathFollower;

class Actor : public Entity
{
public:
	Actor();
	~Actor();
	float getActorSpeed();
	void setActorSpeed(float speed);
	void draw(sf::RenderWindow& window);
	PathFollower* pathComponent();
private:
	PathFollower* m_PathComponent;
	float m_actorSpeed;
};

