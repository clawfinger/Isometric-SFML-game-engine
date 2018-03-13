#include "stdafx.h"
#include "CommandDispatcher.h"

CommandDispatcher::CommandDispatcher(Map& map, Window& window)
{
	// create executor and insert to m_executors, key is command.name()
	m_executors[TypeNameResolver<SetPathCommand>::typeName()] = new SetPathCommandExecutor(map);
	m_executors[TypeNameResolver<ViewMoveCommand>::typeName()] = new ViewMoveCommandExecutor(window);
}

void CommandDispatcher::execute(ICommand* command)
{
	if (m_executors.find(command->name()) != m_executors.end())
		m_executors[command->name()]->execute(command);
	else
		std::cout << "ERROR: Cannot find executor for " << command->name() << std::endl;
}

