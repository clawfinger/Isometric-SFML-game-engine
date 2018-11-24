#include "PathComponent.h"


PathComponent::PathComponent() : ComponentBase(typeName<PathComponent>())
{
}


PathComponent::~PathComponent()
{
}

void PathComponent::setPath(const std::stack<sf::Vector2f>& path, int pathEnd)
{
	if (pathEnd != m_pathEnd)
	{
		m_path = path;
		m_pathEnd = pathEnd;
	}
}

std::stack<sf::Vector2f>& PathComponent::getPath()
{
	return m_path;
}

int PathComponent::getPathEnd()
{
	return m_pathEnd;
}

bool PathComponent::isPathSet()
{
	return !m_path.empty();
}

void PathComponent::readData(std::stringstream & stream)
{
}
