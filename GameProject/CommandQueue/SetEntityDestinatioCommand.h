#pragma once
#include "CommandBase.h"
#include "../ECS/Entity.h"

class SetEntityDestinatioCommand : public CommandBase
{
public:
    SetEntityDestinatioCommand(std::shared_ptr<EventDispatcher> dispatcher, EntityId id, const Vector2f& targetPos);
    ~SetEntityDestinatioCommand();
    void execute() override;
    bool isCompleted() override;
    void update(sf::Time deltaTime) override;

private:
    void handleEntityReachTileEvent(IEvent* event);

private:
    Vector2f m_targetPos;
    EntityId m_id;
};
