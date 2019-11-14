#include "Events.h"

std::string EntityCreatedEvent::name()
{
	return typeName<EntityCreatedEvent>();
}

SetDestinationForEntityEvent::SetDestinationForEntityEvent(EntityId entity, const Vector2f& index):
    entity(entity), destination(index)
{
}

std::string SetDestinationForEntityEvent::name()
{
	return typeName<SetDestinationForEntityEvent>();
}

std::string PlayerReachTileEvent::name()
{
	return typeName<PlayerReachTileEvent>();
}

std::string MapCreatedEvent::name()
{
	return typeName<MapCreatedEvent>();
}

std::string EntityChangedOrientationEvent::name()
{
	return typeName<EntityChangedOrientationEvent>();
}

std::string BattleStartedEvent::name()
{
	return typeName<BattleStartedEvent>();
}

std::string GameStateActivatedEvent::name()
{
    return typeName<GameStateActivatedEvent>();
}
