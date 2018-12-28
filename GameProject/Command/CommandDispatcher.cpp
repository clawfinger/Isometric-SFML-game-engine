#include "CommandDispatcher.h"
#include "../Utils/Logger.h"

CommandDispatcher::CommandDispatcher(Map& map, Window& window)
{
	// create executor and insert to m_executors, key is command.name()
	m_executors[typeName<SetPathCommand>()] = new SetPathCommandExecutor(map);
	m_executors[typeName<ViewMoveCommand>()] = new ViewMoveCommandExecutor(window);
}

CommandDispatcher::~CommandDispatcher()
{
	for (auto executor : m_executors)
	{
		delete executor.second;
	}
}

void CommandDispatcher::execute(ICommand* command)
{
	if (m_executors.find(command->name()) != m_executors.end())
		m_executors[command->name()]->execute(command);
	else
		LOG("ERROR: Cannot find executor for " + command->name());
}

