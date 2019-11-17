#pragma once
#include "../Utils/utility.h"
#include "../Utils/Meta.h"
#include "../Utils/Vector2D.h"
#include "../ECS/Entity.h"
#include "../LevelInfo.h"
#include "../GameState.h"

class IEvent
{
public:
	virtual std::string name() = 0;
    virtual ~IEvent();
};

class EntityCreatedEvent : public IEvent
{
public:
	EntityCreatedEvent(EntityId id, StringList components)
        : id(id), components(components) {}
	std::string name();
	EntityId id;
	StringList components;
};
REGISTER_TYPENAME(EntityCreatedEvent)

class SetDestinationForEntityEvent : public IEvent
{
public:
	SetDestinationForEntityEvent(EntityId entity, const Vector2f& mapIndex);
	std::string name();
	EntityId entity;
	Vector2f destination;
};
REGISTER_TYPENAME(SetDestinationForEntityEvent)

class PlayerReachTileEvent : public IEvent
{
public:
	PlayerReachTileEvent(Vector2f pos, EntityId entity) : pos(pos), entity(entity) {}
	std::string name();
	Vector2f pos;
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

class BattleStartedEvent : public IEvent
{
public:
	BattleStartedEvent(std::vector<EntityId> enemies) : enemies(enemies) {}
	std::string name();
	std::vector<EntityId> enemies;
};
REGISTER_TYPENAME(BattleStartedEvent)

class GameStateActivatedEvent : public IEvent
{
public:
    GameStateActivatedEvent(GameStateId state) : state(state) {}
    std::string name();
    GameStateId state;
};
REGISTER_TYPENAME(GameStateActivatedEvent)

class PartySlotActiveEvent : public IEvent
{
public:
    PartySlotActiveEvent(int pos) : pos(pos) {}
    std::string name();
    int pos;
};
REGISTER_TYPENAME(PartySlotActiveEvent)
