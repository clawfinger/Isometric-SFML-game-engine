#include "stdafx.h"
#include "Events.h"

std::string EntityCreatedEvent::name()
{
	return typeName<EntityCreatedEvent>();
}

SetDestinationForEntityEvent::SetDestinationForEntityEvent(EntityId entity, int index):
	mapIndex(index), entity(entity)
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
