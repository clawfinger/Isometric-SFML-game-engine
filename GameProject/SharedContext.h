#pragma once
//#include "Window.h"
//#include "Map.h"
//#include "CommandDispatcher.h"
//#include "TextureManager.h"

class Window;
class Map;
class CommandDispatcher;
class TextureManager;
class EventDispatcher;
class ILogger;

struct StateSharedContext
{
	Window* window;
	Map* map;
	CommandDispatcher* commandDispatcher;
	EventDispatcher* eventDispatcher;
	TextureManager* textureManager;
};