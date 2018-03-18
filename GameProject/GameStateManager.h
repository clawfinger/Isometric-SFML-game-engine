#pragma once
#include <stack>
#include <map>
#include <functional>

class GameStateBase;
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
	void activateState(GameStateType state);
	void deactivateState();
	template<typename T>
	void registerStateFactory(GameStateType state);
private:
	std::stack<GameStateBase*> m_statesStack;
	std::map<GameStateType, std::function<GameStateBase* (void)>> m_stateFactories;
};

template<typename T>
inline void GameStateManager::registerStateFactory(GameStateType state)
{
	m_stateFactories[state] = [this]()->GameStateBase*
	{
		return new T();
	}
}
