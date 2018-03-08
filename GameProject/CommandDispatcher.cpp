#include "stdafx.h"
#include "CommandDispatcher.h"

CommandDispatcher::CommandDispatcher(Map& map)
{
	// create executor and insert to m_executors, key is command.name()
	m_executors[TypeNameResolver<SetPathCommand>::typeName()] = new SetPathCommandExecutor(map);
}

void CommandDispatcher::execute(ICommand* command)
{
	if (m_executors.find(command->name()) != m_executors.end())
		m_executors[command->name()]->execute(command);
	else
		std::cout << "ERROR: Cannot find executor for " << command->name() << std::endl;
}

