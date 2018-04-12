#pragma once
#include <stack>
#include <map>
#include <functional>
#include "../Utils/Meta.h"

class GameStateBase;
class DiContainer;

enum GameStateType
{
	level = 1
};


class GameStateManager
{
public:
	GameStateManager();
	~GameStateManager();
	GameStateBase* currentState();
	void setContainer(DiContainer* container);
	void activateState(GameStateType state);
	void deactivateCurrentState();
	template<typename T>
	void registerStateFactory(GameStateType state);
private:
	DiContainer* m_container;
	std::stack<GameStateBase*> m_statesStack;
	std::map<GameStateType, std::function<GameStateBase* (void)>> m_stateFactories;
};
REGISTER_TYPENAME(GameStateManager)


template<typename T>
inline void GameStateManager::registerStateFactory(GameStateType state)
{
	m_stateFactories[state] = [this]()->GameStateBase*
	{
		return new T();
	};
}
