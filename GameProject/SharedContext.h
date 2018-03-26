#pragma once
#include "Window.h"
#include "Map.h"
#include "CommandDispatcher.h"
#include "Player.h"
#include "TextureManager.h"

struct StateSharedContext
{
	Window* window;
	Map* map;
	CommandDispatcher* commandDispatcher;
	TextureManager* textureManager;
	Player* player;
};