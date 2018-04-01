#pragma once
#include "TextureManager.h"
#include "Command/CommandDispatcher.h"
#include "Events/EventDispatcher.h"
#include "window.h"
#include "Map.h"
#include "State/GameStateManager.h"
#include <vector>
#include <list>
#include <memory>


class Game
{
public:
	Game();
	void run();
private:
	void processEvents();
	void update(sf::Time deltaTime);
	void render();

private:
	//MEMBER ORDER MATTERS!
	GameStateManager m_stateManager;
	TextureManager m_textureManager;
	EventDispatcher m_eventDispatcher;

	bool isRunning;
	sf::Time m_timePerFrame;
	Window m_window;
	sf::View view;
	Map m_map;
	CommandDispatcher m_commandDispatcher;
};
