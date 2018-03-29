#pragma once
#include <SFML/Graphics.hpp>
#include "PathFollower.h"
#include "Entity.h"


class Actor : public Entity
{
public:
	Actor();
	float getActorSpeed();
	void setActorSpeed(float speed);
	void draw(sf::RenderWindow& window);
	PathFollower& pathComponent();
private:
	PathFollower m_PathComponent;
	float m_actorSpeed;
};

