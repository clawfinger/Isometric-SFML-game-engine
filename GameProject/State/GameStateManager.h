#pragma once
#include <stack>
#include <map>
#include <functional>
#include "../GameState.h"
#include "../Utils/Meta.h"

class GameStateBase;
class DiContainer;

class GameStateManager
{
public:
	GameStateManager();
	~GameStateManager();
	GameStateBase* currentState();
	void setContainer(DiContainer* container);
	void activateState(GameStateId state);
	void deactivateCurrentState();
	template<typename T>
	void registerStateFactory(GameStateId state);
private:
	DiContainer* m_container;
	std::stack<GameStateBase*> m_statesStack;
	std::map<GameStateId, std::function<GameStateBase* (void)>> m_stateFactories;
};
REGISTER_TYPENAME(GameStateManager)


template<typename T>
inline void GameStateManager::registerStateFactory(GameStateId state)
{
	m_stateFactories[state] = [this]()->GameStateBase*
	{
		return new T(m_container);
	};
}
