#pragma once
#include <unordered_map>
#include "GameStateBase.h"
#include "../SharedContext.h"
#include "SFML/Graphics.hpp"
#include "../Actor.h"
#include "../GameEngine.h"

class GameLevelState : public GameStateBase
{
public:
	GameLevelState(StateSharedContext* context);
	~GameLevelState();
	void update(sf::Time deltaTime);
	void render();
	void handlePlayerInput(sf::Event& event);
private:
	void handleKeyboardInput(sf::Keyboard::Key key);
	void handleMouseInput(sf::Vector2i mouseCoords);
private:
	StateSharedContext* m_sharedContext;
	GameEngine m_gameEngine;
};

