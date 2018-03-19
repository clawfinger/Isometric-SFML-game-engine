#include "stdafx.h"
#include "GameStateManager.h"
#include "GameLevelState.h"

GameStateManager::GameStateManager()
{
	registerStateFactory<GameLevelState>(GameStateType::level);
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

void GameStateManager::setSharedContext(StateSharedContext context)
{
	m_sharedContext = context;
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
