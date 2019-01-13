#include "EntityStateComponent.h"


EntityStateComponent::EntityStateComponent(): ComponentBase(typeName<EntityStateComponent>()), m_state(EntityState::idle)
{
}


EntityStateComponent::~EntityStateComponent()
{
}

void EntityStateComponent::readData(std::stringstream & l_stream)
{
}

std::string& EntityStateComponent::getState()
{
	return m_state;
}

void EntityStateComponent::setState(const std::string& state)
{
	m_state = state;
}
