#pragma once
#include "Base/GuiEventController.h"

class GameLevelController : public GuiEventController
{
public:
    GameLevelController(std::shared_ptr<EventDispatcher> dispatcher);
    void elementPressed(const std::string& name) const override;
};
