#pragma once
#include <stack>
#include <map>
#include <functional>
#include "../SharedContext.h"
#include "../Utils/Meta.h"

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
	void setSharedContext(StateSharedContext* context);
	void activateState(GameStateType state);
	void deactivateState();
	template<typename T>
	void registerStateFactory(GameStateType state);
private:
	StateSharedContext* m_sharedContext;
	std::stack<GameStateBase*> m_statesStack;
	std::map<GameStateType, std::function<GameStateBase* (void)>> m_stateFactories;
};
REGISTER_TYPENAME(GameStateManager)


template<typename T>
inline void GameStateManager::registerStateFactory(GameStateType state)
{
	m_stateFactories[state] = [this]()->GameStateBase*
	{
		return new T(m_sharedContext);
	};
}
