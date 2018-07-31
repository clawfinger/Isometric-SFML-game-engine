#pragma once
#include "../Utils/utility.h"
#include "../Utils/Meta.h"
#include "../ECS/Entity.h"
#include "../LevelInfo.h"

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
	PlayerReachTileEvent(sf::Vector2f pos, EntityId entity) : pos(pos), entity(entity) {}
	std::string name();
	sf::Vector2f pos;
	EntityId entity;
};
REGISTER_TYPENAME(PlayerReachTileEvent)

class MapCreatedEvent: public IEvent
{
public:
	MapCreatedEvent(LevelTypes currentMap) : mapType(currentMap) {}
	std::string name();
	LevelTypes mapType;
};
REGISTER_TYPENAME(MapCreatedEvent)

class EntityChangedOrientationEvent : public IEvent
{
public:
	EntityChangedOrientationEvent(EntityId entity) : entity(entity) {}
	std::string name();
	EntityId entity;
};
REGISTER_TYPENAME(EntityChangedOrientationEvent)