#include "stdafx.h"
#include "GameStateManager.h"


GameStateManager::GameStateManager()
{
}


GameStateManager::~GameStateManager()
{
}

GameStateBase * GameStateManager::currentState()
{
	if (m_statesStack.empty())
		return nullptr;
	else
		return m_statesStack.top();
}

void GameStateManager::activateState(GameStateType state)
{
	auto stateFactory = m_stateFactories[state];
	m_statesStack.push(stateFactory());
}

void GameStateManager::deactivateState()
{
	m_statesStack.pop();
}
