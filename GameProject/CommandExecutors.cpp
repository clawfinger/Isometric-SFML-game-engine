#include "stdafx.h"
#include "CommandExecutors.h"
#include "PathFollower.h"

void SetPathCommandExecutor::execute(ICommand* command)
{
	SetPathCommand* concreteCommand = static_cast<SetPathCommand*>(command);

	if (concreteCommand == nullptr)
	{
		std::cout << "ERROR: Wrong command passed to SetPathCommandExecutor" << std::endl;
	}
	else
	{
		if (concreteCommand->m_unit->pathComponent().getPathEnd() != concreteCommand->m_destination)
		{
			sf::Vector2f playerPosition = concreteCommand->m_unit->getPosition();
			int linearMapPlayerPosition = m_map.mapFromWindow(playerPosition.x, playerPosition.y);
			concreteCommand->m_unit->pathComponent().setPath(m_map.calculatePath(linearMapPlayerPosition, concreteCommand->m_destination), concreteCommand->m_destination);
		}
	}
}

void ViewMoveCommandExecutor::execute(ICommand * command)
{
	ViewMoveCommand* concreteCommand = static_cast<ViewMoveCommand*>(command);
	if (concreteCommand == nullptr)
	{
		std::cout << "ERROR: Wrong command passed to ViewMoveCommandExecutor" << std::endl;
	}
	else
	{
		sf::Vector2f viewMovement(0.0f, 0.0f);
		viewMovement += (sf::Vector2f(concreteCommand->x_movement, concreteCommand->y_movement) * concreteCommand->m_speed);
		m_window.moveView(viewMovement);
	}
}
