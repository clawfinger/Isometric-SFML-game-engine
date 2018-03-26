#pragma once
#include "Window.h"
#include "Map.h"
#include "CommandDispatcher.h"
#include "TextureManager.h"

class ActorManager;
struct StateSharedContext
{
	Window* window;
	Map* map;
	CommandDispatcher* commandDispatcher;
	TextureManager* textureManager;
	ActorManager* actorManager;
};