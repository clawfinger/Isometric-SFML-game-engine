#include "CommandQueue.h"
#include "../Events/EventDispatcher.h"

CommandQueue::CommandQueue(std::shared_ptr<EventDispatcher> dispatcher): m_dispatcher(dispatcher)
{

}

void CommandQueue::update(sf::Time deltaTime)
{
    if (m_commandQueue.empty())
        return;

    m_commandQueue.front().update(deltaTime);

    if (m_commandQueue.front().isCompleted())
        m_commandQueue.pop();
}
