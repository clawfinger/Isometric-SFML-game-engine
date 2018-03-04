#include "stdafx.h"
#include "CommandExecutors.h"
#include "PathFollower.h"

void SetPathCommandExecutor::execute(ICommand* command)
{
	std::unique_ptr<SetPathCommand> concreteCommand(dynamic_cast<SetPathCommand*>(command));

	if (concreteCommand.get() == nullptr)
	{
		std::cout << "ERROR: Wrong command passed to SetPathCommandExecutor" << std::endl;
	}
	else
	{
		if (concreteCommand->m_unit->getPathEnd() != concreteCommand->m_destination)
		{
			sf::Vector2f playerPosition = concreteCommand->m_unit->getPosition();
			int linearMapPlayerPosition = m_map.mapFromWindow(playerPosition.x, playerPosition.y);
			concreteCommand->m_unit->setPath(m_map.calculatePath(linearMapPlayerPosition, concreteCommand->m_destination), concreteCommand->m_destination);
		}
	}
}
