#include "stdafx.h"
#include "PathFollower.h"


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
