#pragma once
#include <stack>
#include <map>
#include <memory>
#include <functional>
#include "../GameState.h"
#include "../Utils/Meta.h"

class GameStateBase;
class DiContainer;
class EventDispatcher;

class GameStateManager
{
public:
    GameStateManager(std::shared_ptr<EventDispatcher> dispatcher);
	~GameStateManager();
	GameStateBase* currentState();
	void setContainer(DiContainer* container);
	void activateState(GameStateId state);
	void deactivateCurrentState();
	template<typename T>
	void registerStateFactory(GameStateId state);
private:
	DiContainer* m_container;
    std::shared_ptr<EventDispatcher> m_dispatcher;
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
