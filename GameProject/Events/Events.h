#pragma once
#include "../Utils/utility.h"
#include "../Utils/Meta.h"
#include "../ECS/Entity.h"

class IEvent
{
public:
	virtual std::string name() = 0;
	virtual ~IEvent() {};
};

class EntityCreatedEvent : public IEvent
{
public:
	EntityCreatedEvent(EntityId id, StringList components)
		: id(id), components(components) {};
	std::string name();
	EntityId id;
	StringList components;
};
REGISTER_TYPENAME(EntityCreatedEvent)

class SetDestinationForEntityEvent : public IEvent
{
public:
	SetDestinationForEntityEvent(EntityId entity, int index);
	std::string name();
	EntityId entity;
	int mapIndex;
};
REGISTER_TYPENAME(SetDestinationForEntityEvent)

class PlayerReachTileEvent : public IEvent
{
public:
	PlayerReachTileEvent(sf::Vector2f pos) : pos(pos) {}
	std::string name();
	sf::Vector2f pos;
};
REGISTER_TYPENAME(PlayerReachTileEvent)

class MapCreatedEvent: public IEvent
{
	std::string name();
};
REGISTER_TYPENAME(MapCreatedEvent)