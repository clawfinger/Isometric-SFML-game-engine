#include "stdafx.h"
#include "PathFollower.h"
#include "utility.h"
#include "Actor.h"

PathFollower::PathFollower(Actor* actor) : m_actor(actor)
{
}

void PathFollower::setPath(std::stack<sf::Vector2f> path, int pathEnd)
{
	m_currentPath = path;
	m_pathEnd = pathEnd;
}

int PathFollower::getPathEnd()
{
	return m_pathEnd;
}

bool PathFollower::isPathSet()
{
	return !m_currentPath.empty();
}

std::stack<sf::Vector2f>& PathFollower::getPath()
{
	return m_currentPath;
}

void PathFollower::update(sf::Time elapsed)
{
	if (isPathSet())
	{
		if (getPath().top() != m_actor->getPosition())
		{
			sf::Vector2f playerMoveVector = getPath().top() - m_actor->getPosition();
			sf::Vector2f normalazedVector = Vector::normalize<sf::Vector2f>(playerMoveVector);
			sf::Vector2f movement = normalazedVector * elapsed.asSeconds() * m_actor->getActorSpeed();
			if (Vector::length<sf::Vector2f>(playerMoveVector) < Vector::length<sf::Vector2f>(movement))
			{
				m_actor->setPosition(getPath().top());
				getPath().pop();
			}
			else
			{
				m_actor->move(movement);
			}

		}
		else
		{
			getPath().pop();
		}
	}
}
