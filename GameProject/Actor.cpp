#include "stdafx.h"
#include "Actor.h"
#include "PathFollower.h"

Actor::Actor()
{
	m_PathComponent = new PathFollower(this);
	m_actorSpeed = 200.0;
}

Actor::~Actor()
{
	delete m_PathComponent;
}

float Actor::getActorSpeed()
{
	return m_actorSpeed;
}

void Actor::setActorSpeed(float speed)
{
	m_actorSpeed = speed;
}

void Actor::draw(sf::RenderWindow & window)
{
	window.draw(getSprite());
}

PathFollower* Actor::pathComponent()
{
	return m_PathComponent;
}
