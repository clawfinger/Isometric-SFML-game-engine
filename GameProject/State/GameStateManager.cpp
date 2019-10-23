#include "GameStateManager.h"
#include "GameLevelState.h"
#include <string>
#include "../Utils/Logger.h"

GameStateManager::GameStateManager()
{
	registerStateFactory<GameLevelState>(GameStateId::level);
}


GameStateManager::~GameStateManager()
{
	while (!m_statesStack.empty())
	{
		deactivateCurrentState();
	}
}

GameStateBase * GameStateManager::currentState()
{
	if (m_statesStack.empty())
		return nullptr;
	else
		return m_statesStack.top();
}

void GameStateManager::setContainer(DiContainer* container)
{
	m_container = container;
}

void GameStateManager::activateState(GameStateId state)
{
	auto stateFactory = m_stateFactories.find(state);
	if (stateFactory == m_stateFactories.end())
		LOG("ERROR: Cannot find factory for state: " + std::to_string(state));
	else
		m_statesStack.push(stateFactory->second());
}

void GameStateManager::deactivateCurrentState()
{
	m_statesStack.top()->onDeactivate();
	delete m_statesStack.top();
	m_statesStack.pop();
}
