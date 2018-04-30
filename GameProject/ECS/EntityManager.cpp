#include "stdafx.h"
#include "EntityManager.h"


EntityManager::EntityManager(std::shared_ptr<EntityContainer> entityContainer,
	std::shared_ptr<EventDispatcher> eventDispatcher):
	m_entityContainer(entityContainer), m_eventDispatcher(eventDispatcher)
{
}


EntityManager::~EntityManager()
{
}
