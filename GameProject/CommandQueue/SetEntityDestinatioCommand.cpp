#include "SetEntityDestinatioCommand.h"
#include "../Events/EventDispatcher.h"
#include "../Events/Events.h"

SetEntityDestinatioCommand::SetEntityDestinatioCommand(std::shared_ptr<EventDispatcher> dispatcher, EntityId id, const Vector2f &targetPos):
    CommandBase(dispatcher), m_targetPos(targetPos), m_id(id)
{
    m_dispatcher->subscribe(typeName<PlayerReachTileEvent>(), this);
    registerCallBack(typeName<PlayerReachTileEvent>(), std::bind(&SetEntityDestinatioCommand::handleEntityReachTileEvent, this, std::placeholders::_1));
}

SetEntityDestinatioCommand::~SetEntityDestinatioCommand()
{
    m_dispatcher->unsubscribe(typeName<PlayerReachTileEvent>(), this);
}

void SetEntityDestinatioCommand::execute()
{
    m_dispatcher->dispatch<SetDestinationForEntityEvent>(m_id, m_targetPos);
}

bool SetEntityDestinatioCommand::isCompleted()
{
    return m_isCompleted;
}

void SetEntityDestinatioCommand::update(sf::Time deltaTime)
{

}

void SetEntityDestinatioCommand::handleEntityReachTileEvent(IEvent *event)
{
    PlayerReachTileEvent *currentEvent = dynamic_cast<PlayerReachTileEvent *>(event);
    if (nullptr == currentEvent)
        return;

    if (currentEvent->pos == m_targetPos)
        m_isCompleted = true;
}
