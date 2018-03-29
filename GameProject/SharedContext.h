#pragma once
//#include "Window.h"
//#include "Map.h"
//#include "CommandDispatcher.h"
//#include "TextureManager.h"

class Window;
class Map;
class CommandDispatcher;
class TextureManager;

struct StateSharedContext
{
	Window* window;
	Map* map;
	CommandDispatcher* commandDispatcher;
	TextureManager* textureManager;
};