#pragma once
#include "TextureManager.h"
#include "CommandDispatcher.h"
#include "window.h"
#include "Map.h"
#include "Player.h"
#include "GameStateManager.h"
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
	bool isRunning;
	TextureManager m_textureManager;
	sf::Time m_timePerFrame;
	Window m_window;
	sf::View view;
	Player m_player;
	Map m_map;
	CommandDispatcher m_commandDispatcher;
	GameStateManager m_stateManager;
};
