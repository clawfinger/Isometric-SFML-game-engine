#pragma once
#include <unordered_map>
#include "SharedContext.h"
#include "Actor.h"
#include "ActorManager.h"

class GameEngine
{
public:
	GameEngine(StateSharedContext* context);
	~GameEngine();
	void draw(sf::RenderWindow& window);
	void update(sf::Time deltaTime);
	void setActiveCharacter(std::string id);
	void createCharacter(std::string id);
	void createEnemy(std::string id);
	Actor* activeCharacter();
private:
	Actor* m_activeCharacter;
	ActorManager m_actorManager;
	std::unordered_map<std::string, Actor*> m_team;
	std::unordered_map<std::string, Actor*> m_enemies;
	StateSharedContext* m_sharedContext;
};

