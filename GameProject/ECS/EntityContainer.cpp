#include "stdafx.h"
#include "EntityContainer.h"
#include "Components/PathComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/PositionComponent.h"
#include "Components/AIControlledComponent.h"
#include "Components/SpriteOrientationComponent.h"
#include "../Events/Events.h"
#include "../Utils/Meta.h"

EntityContainer::EntityContainer() : m_idCounter(0)
{
	//register component factories
	registerComponentFactory<PathComponent>(typeName<PathComponent>());
	registerComponentFactory<SpriteComponent>(typeName<SpriteComponent>());
	registerComponentFactory<PositionComponent>(typeName<PositionComponent>());
	registerComponentFactory<AIControlledComponent>(typeName<AIControlledComponent>());
	registerComponentFactory<SpriteOrientationComponent>(typeName<SpriteOrientationComponent>());
}


EntityContainer::~EntityContainer()
{
}

EntityId EntityContainer::createEntity(const StringList & componentList)
{
	EntityId newEntityId = m_idCounter++;
	//TODO: Move component creation to object pool to prevent memory fragmentation
	m_entityContainer.emplace(newEntityId, EntityData(componentList, std::vector<ComponentBase*>()));
	for (const std::string& component : componentList)
	{
		addComponentToEntity(newEntityId, component);
	}
	return newEntityId;
}

void EntityContainer::removeEntity(EntityId id)
{
	auto entityDataIter = m_entityContainer.find(id);
	if (entityDataIter != m_entityContainer.end())
	{
		while (entityDataIter->second.second.begin() != entityDataIter->second.second.end())
		{
			delete entityDataIter->second.second.back();
			entityDataIter->second.second.pop_back();
		}
		m_entityContainer.erase(entityDataIter);
	}
}

bool EntityContainer::HasComponent(EntityId id, const std::string & componentName)
{
	auto entityDataIter = m_entityContainer.find(id);
	if (entityDataIter != m_entityContainer.end())
	{
		if (entityDataIter->second.first.contains(componentName))
		{
			for (auto component : entityDataIter->second.second)
			{
				if (component->name() == componentName)
				{
					return true;
				}
			}
		}
		else
		{
			Logger::instance().log("ERROR: Component " + componentName + " not found in entity with id=" + std::to_string(id));
			return false;
		}
	}
	else
	{
		Logger::instance().log("ERROR: Cannot find Entity data for entity with id=" + std::to_string(id));
		return false;
	}
	return false;
}

void EntityContainer::clearAllEntities()
{

}

void EntityContainer::addComponentToEntity(EntityId id, const std::string & componentName)
{
	auto entityIter = m_entityContainer.find(id);
	if (entityIter != m_entityContainer.end())
	{
		for (const std::string& componentName : entityIter->second.first)
		{
			auto factory = m_componentFactories.find(componentName);
			if (factory != m_componentFactories.end())
				entityIter->second.second.push_back(factory->second());
			else
				Logger::instance().log("ERROR: Cannot find factory for component " + componentName + " while adding to " + std::to_string(id));
		}
	}
	else
	{
		Logger::instance().log("ERROR: Cannot find Entity data for entity with id=" + std::to_string(id));
		return;
	}
}
