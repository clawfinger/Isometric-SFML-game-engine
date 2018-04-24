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

class FloorTileClickedEvent : public IEvent
{
public:
	FloorTileClickedEvent(int index);
	std::string name();
	int mapIndex;
};
REGISTER_TYPENAME(FloorTileClickedEvent)

class CurrentPlayerChangedEvent : public IEvent
{
public:
	CurrentPlayerChangedEvent(EntityId id) : id(id) {}
	std::string name();
	EntityId id;
};
REGISTER_TYPENAME(CurrentPlayerChangedEvent)

class PlayerReachTileEvent : public IEvent
{
public:
	PlayerReachTileEvent(sf::Vector2f pos) : pos(pos) {}
	std::string name();
	sf::Vector2f pos;
};
REGISTER_TYPENAME(PlayerReachTileEvent)