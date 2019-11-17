#include "Layout.h"
#include "../../Utils/Logger.h"

Layout::Layout(const std::string &name, const GuiEventController &controller, Widget *parent):
    Widget(name, controller, parent)
{
    m_background.setFillColor(sf::Color(0, 0, 0, 95));
    m_background.setOutlineThickness(2);
    m_background.setOutlineColor(sf::Color(215, 183, 64));
}

void Layout::onMousePress(const Vector2D<int>& mousePos)
{
    Widget::onMousePress(mousePos);
    for (auto child: m_children)
    {
        if (child.second->isInside(mousePos))
            child.second->onMousePress(mousePos);
    }
}

void Layout::onMouseRelease(const Vector2D<int>& mousePos)
{
    Widget::onMouseRelease(mousePos);
    for (auto child: m_children)
    {
        if (child.second->isInside(mousePos))
            child.second->onMouseRelease(mousePos);
    }
}

void Layout::onMouseHover(const Vector2D<int> &mousePos)
{
    Widget::onMouseHover(mousePos);
    for (auto child: m_children)
    {
        if (child.second->isInside(mousePos))
            child.second->onMouseHover(mousePos);
        else if (child.second->getState() == WidgetState::HOVER)
            child.second->onMouseLeave();
    }
}

void Layout::onMouseLeave()
{
    Widget::onMouseLeave();
    for (auto child: m_children)
    {
        child.second->onMouseLeave();
    }
}

void Layout::update(sf::Time deltaTime, const Vector2D<int> &mousePos)
{
    Widget::update(deltaTime, mousePos);
    for (auto child: m_children)
        child.second->update(deltaTime, mousePos);
}

void Layout::draw(sf::RenderTarget *target)
{
    target->draw(m_background);
    for (auto child: m_children)
        child.second->draw(target);
}

void Layout::setPosition(const Vector2D<int> &pos)
{
    Widget::setPosition(pos);
    adjustContent();
}

void Layout::setSize(const Vector2D<int> &size)
{
    Widget::setSize(size);
    adjustContent();
}

void Layout::setState(const WidgetState &state)
{
    if (getState() == state)
        return;

    Widget::setState(state);
    if (state == WidgetState::HOVER)
        m_background.setFillColor(sf::Color(255, 0, 0, 95));
    else
        m_background.setFillColor(sf::Color(0, 0, 0, 95));
}

void Layout::addWidget(Widget *child)
{
    if (m_children.count(child->getName()) > 1)
    {
        LOG("Layout already have widget with name " + child->getName());
    }
    m_children[child->getName()] = child;
}

void Layout::adjustContent()
{
    m_background.setSize(sf::Vector2f(getSize().x, getSize().y));
    Vector2D<int> global = getGlobalPosition();
    m_background.setPosition(global.x, global.y);
    for (auto child: m_children)
        child.second->adjustContent();
}
