#pragma once
#include "GameStateBase.h"
#include "../SharedContext.h"
#include "SFML/Graphics.hpp"

class GameLevelState : public GameStateBase
{
public:
	GameLevelState(StateSharedContext& context);
	~GameLevelState();
	void update(sf::Time deltaTime);
	void render();
	void handlePlayerInput(sf::Event& event);
private:
	void handleKeyboardInput(sf::Keyboard::Key key);
private:
	StateSharedContext m_sharedContext;
};

