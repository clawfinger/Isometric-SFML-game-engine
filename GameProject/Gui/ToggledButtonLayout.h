#pragma once
#include "Base/Layout.h"

class Button;

class ToggledButtonLayout : public Layout
{
public:
    ToggledButtonLayout(const std::string& m_name,
                        const GuiEventController& controller, Widget* parent = nullptr);

    void onMousePress(const Vector2D<int>& mousePos) override;
    void addButton(Button* child);

private:
    std::vector<Button*> m_buttons;
};
