#pragma once
#include "Window.h"
#include "Map.h"
#include "CommandDispatcher.h"
#include "Player.h"


struct StateSharedContext
{
	Window* window;
	Map* map;
	CommandDispatcher* commandDispatcher;
	Player* player;
};