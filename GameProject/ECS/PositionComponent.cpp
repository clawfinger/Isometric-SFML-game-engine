#include "stdafx.h"
#include "PositionComponent.h"


PositionComponent::PositionComponent() : ComponentBase(typeName<PositionComponent>())
{
}


PositionComponent::~PositionComponent()
{
}

sf::Vector2f PositionComponent::getPosition()
{
	return m_position;
}

void PositionComponent::setPosition(const sf::Vector2f & position)
{
	m_position = position;
}

void PositionComponent::move(const sf::Vector2f & movement)
{
	m_position += movement;
}
