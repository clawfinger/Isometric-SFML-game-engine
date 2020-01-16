#pragma once
#include <vector>
#include <unordered_map>
#include <functional>
#include <memory>
#include "../Utils/utility.h"
#include "../Utils/Logger.h"
#include "../Utils/Meta.h"
#include "Components/ComponentBase.h"
#include "Entity.h"

using EntityData = std::pair<StringList, std::vector<ComponentBase*>>;

class EntityContainer
{
public:
	EntityContainer();
	~EntityContainer();
	EntityId createEntity(const StringList& componentList);
	void removeEntity(EntityId id);
	bool HasComponent(EntityId id, const std::string& componentName);
	template<typename T>
    T * getComponent(EntityId id);
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
};
REGISTER_TYPENAME(EntityContainer)

template<typename T>
inline T * EntityContainer::getComponent(EntityId id)
{
    std::string componentName = typeName<T>();
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
			LOG("ERROR: Component " + componentName + " not found in entity with id=" + std::to_string(id));
		}
	}
	else
	{
		LOG("ERROR: Cannot find Entity data for entity with id=" + std::to_string(id));
	}
	return nullptr;
}

	template<typename T>
inline void EntityContainer::registerComponentFactory(const std::string & componentName)
{
	m_componentFactories[componentName] = []()->ComponentBase* { return new T();};
}
