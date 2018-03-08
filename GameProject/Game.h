#pragma once
#include "TextureManager.h"
#include "CommandDispatcher.h"
#include "window.h"
#include "Map.h"
#include "Player.h"
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
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
private:
	bool m_isMovingUp;
	bool m_isMovingDown;
	bool m_isMovingLeft;
	bool m_isMovingRight;
	bool isRunning;
	TextureManager m_textureManager;
	sf::Time m_timePerFrame;
	Window m_window;
	sf::View view;
	float m_viewSpeed;
	int m_mapHeight;
	int m_mapWidth;
	Player m_player;
	Map m_map;
	CommandDispatcher m_commandDispatcher;
};
