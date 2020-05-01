#include "CommandQueue.h"
#include "../Events/EventDispatcher.h"

CommandQueue::CommandQueue(std::shared_ptr<EventDispatcher> dispatcher): m_dispatcher(dispatcher), m_isQueueIdling(true)
{

}

void CommandQueue::update(sf::Time deltaTime)
{
    if (m_commandQueue.empty())
        return;

    if (m_isQueueIdling)
    {
        m_commandQueue.front()->execute();
    }

    m_commandQueue.front()->update(deltaTime);

    if (m_commandQueue.front()->isCompleted())
    {
        m_commandQueue.pop();
        m_isQueueIdling = true;
    }
}

EntityCommandDispatcher::EntityCommandDispatcher(std::shared_ptr<EventDispatcher> dispatcher): m_dispatcher(dispatcher)
{

}

void EntityCommandDispatcher::update(sf::Time deltaTime)
{
    for (auto queue: m_entityQueues)
    {
        queue.second->update(deltaTime);
    }
}

void EntityCommandDispatcher::clearQueues()
{
    m_entityQueues.clear();
}
