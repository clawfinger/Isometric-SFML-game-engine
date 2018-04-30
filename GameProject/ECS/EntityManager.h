#pragma once
#include <memory>
#include <unordered_map>
#include "../Utils/Utility.h"

class EntityContainer;
class EventDispatcher;

class EntityManager
{
public:
	EntityManager(std::shared_ptr<EntityContainer> entityContainer,
		std::shared_ptr<EventDispatcher> eventDispatcher);
	~EntityManager();
private:
	void loadEntityTypes();
private:
	std::shared_ptr<EntityContainer> m_entityContainer;
	std::shared_ptr<EventDispatcher> m_eventDispatcher;
	std::unordered_map<std::string, StringList> m_entityTypes;
};

