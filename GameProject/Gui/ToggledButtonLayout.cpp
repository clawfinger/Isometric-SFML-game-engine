#include "ToggledButtonLayout.h"
#include "Base/Button.h"
#include "../Utils/Logger.h"

ToggledButtonLayout::ToggledButtonLayout(const std::string &m_name,
                                         const GuiEventController &controller, Widget *parent):
    Layout(m_name, controller, parent)
{

}

void ToggledButtonLayout::onMousePress(const Vector2D<int> &mousePos)
{
    Widget::onMousePress(mousePos);
    for (auto button: m_buttons)
    {
        if (button->isInside(mousePos))
        {
            button->onMousePress(mousePos);
            if (!button->isToggled())
            {
                for (auto button: m_buttons)
                {
                    button->setToggled(false);
                }
                button->setToggled(true);
                return;
            }
        }
    }
}

void ToggledButtonLayout::addButton(Button *child)
{
    Layout::addWidget(child);
    m_buttons.push_back(child);
}
