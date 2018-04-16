#include "stdafx.h"
#include "Events.h"

std::string EntityCreatedEvent::name()
{
	return typeName<EntityCreatedEvent>();
}

FloorTileClickedEvent::FloorTileClickedEvent(int index): mapIndex(index)
{
}

std::string FloorTileClickedEvent::name()
{
	return typeName<FloorTileClickedEvent>();
}
