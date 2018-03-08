#include "stdafx.h"
#include "Actor.h"

Actor::Actor() : m_PathComponent()
{
	m_actorSpeed = 200.0;
}

float Actor::getActorSpeed()
{
	return m_actorSpeed;
}

void Actor::setActorSpeed(float speed)
{
	m_actorSpeed = speed;
}

PathFollower& Actor::pathComponent()
{
	return m_PathComponent;
}
