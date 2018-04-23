#pragma once
#include <vector>
#include <unordered_map>
#include <functional>
#include <memory>
#include "../Utils/utility.h"
#include "../Utils/Logger.h"
#include "../Utils/Meta.h"
#include "../Events/EventDispatcher.h"
#include "Components/ComponentBase.h"
#include "Entity.h"

using EntityData = std::pair<StringList, std::vector<ComponentBase*>>;

class EntityManager
{
public:
	EntityManager(std::shared_ptr<EventDispatcher> eventDispatcher);
	~EntityManager();
	EntityId createEntity(const StringList& componentList);
	void removeEntity(EntityId id);
	bool HasComponent(EntityId id, const std::string& componentName);
	template<typename T>
	T * getComponent(EntityId id, const std::string& componentName);
	void clearAllEntities();
private:
	void addComponentToEntity(EntityId id, const std::string& componentName);
	template<typename T>
	void registerComponentFactory(const std::string& componentName);

private:
	EntityId m_idCounter;
	std::vector<ComponentBase*> m_entityComponents;
	std::unordered_map <EntityId, EntityData> m_entityContainer;
	std::unordered_map<std::string, std::function<ComponentBase*(void)>> m_componentFactories;
	std::shared_ptr<EventDispatcher> m_eventDispatcher;
};
REGISTER_TYPENAME(EntityManager)

template<typename T>
inline T * EntityManager::getComponent(EntityId id, const std::string & componentName)
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
					return dynamic_cast<T*>(component);
				}
			}
		}
		else
		{
			Logger::instance().log("ERROR: Component " + componentName + " not found in entity with id=" + std::to_string(id));
		}
	}
	else
	{
		Logger::instance().log("ERROR: Cannot find Entity data for entity with id=" + std::to_string(id));
	}
	return nullptr;
}

	template<typename T>
inline void EntityManager::registerComponentFactory(const std::string & componentName)
{
	m_componentFactories[componentName] = []()->ComponentBase* { return new T();};
}