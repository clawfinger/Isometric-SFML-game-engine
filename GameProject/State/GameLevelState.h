#pragma once
#include <unordered_map>
#include "GameStateBase.h"
#include "../SharedContext.h"
#include "SFML/Graphics.hpp"
#include "../Actor.h"

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
	std::unordered_map<std::string, Actor*> m_enemies;
};

