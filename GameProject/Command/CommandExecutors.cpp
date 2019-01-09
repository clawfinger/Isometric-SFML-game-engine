#include "CommandExecutors.h"
#include "../Utils/Logger.h"

void SetPathCommandExecutor::execute(ICommand* command)
{
	SetPathCommand* concreteCommand = static_cast<SetPathCommand*>(command);

	//if (concreteCommand == nullptr)
	//{
	//	LOG("ERROR: Wrong command passed to SetPathCommandExecutor");
	//}
	//else
	//{
	//	if (concreteCommand->m_unit->pathComponent()->getPathEnd() != concreteCommand->m_destination)
	//	{
	//		Vector2f playerPosition = concreteCommand->m_unit->getPosition();
	//		int linearMapPlayerPosition = m_map.mapIndexFromWindow(playerPosition.x, playerPosition.y);
	//		std::stack<Vector2f> newPath = m_map.calculatePath(linearMapPlayerPosition, concreteCommand->m_destination);
	//		newPath.push(m_map.windowFromMap(m_map.XYfromLinear(linearMapPlayerPosition)));
	//		concreteCommand->m_unit->pathComponent()->setPath(newPath, concreteCommand->m_destination);
	//	}
	//}
}

void ViewMoveCommandExecutor::execute(ICommand * command)
{
	ViewMoveCommand* concreteCommand = static_cast<ViewMoveCommand*>(command);
	//if (concreteCommand == nullptr)
	//{
	//	LOG("ERROR: Wrong command passed to ViewMoveCommandExecutor");
	//}
	//else
	//{
	//	m_window.setViewMoveVector(Vector2f(concreteCommand->x_direction, concreteCommand->y_direction) * concreteCommand->m_speed);
	//}
}
