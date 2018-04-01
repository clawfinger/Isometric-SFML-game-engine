#include "stdafx.h"
#include "GameStateManager.h"
#include "GameLevelState.h"
#include <string>
#include "../Logger.h"

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

void GameStateManager::setSharedContext(StateSharedContext* context)
{
	m_sharedContext = context;
}

void GameStateManager::activateState(GameStateType state)
{
	auto stateFactory = m_stateFactories.find(state);
	if (stateFactory == m_stateFactories.end())
		Logger::instance().log("ERROR: Cannot find factory for state: " + std::to_string(state));
	else
		m_statesStack.push(stateFactory->second());
}

void GameStateManager::deactivateState()
{
	m_statesStack.pop();
}
