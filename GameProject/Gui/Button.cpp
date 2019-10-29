#include "Button.h"

Button::Button(const std::string &name, Widget *parent): Widget(name, parent)
{
    m_background.setFillColor(sf::Color(0, 0, 0, 95));
    m_background.setOutlineThickness(1);
    m_background.setOutlineColor(sf::Color(sf::Color::Black));
    setHoverable(true);
}

void Button::onMousePress(const Vector2D<int> &mousePos)
{
    Widget::onMousePress(mousePos);
}

void Button::onMouseRelease(const Vector2D<int> &mousePos)
{
    Widget::onMouseRelease(mousePos);
}

void Button::onMouseHover(const Vector2D<int> &mousePos)
{
    Widget::onMouseHover(mousePos);
}

void Button::onMouseLeave()
{
    Widget::onMouseLeave();
}

void Button::update(sf::Time deltaTime, const Vector2D<int> &mousePos)
{
    Widget::update(deltaTime, mousePos);
}

void Button::draw(sf::RenderTarget *target)
{
    target->draw(m_background);
}

void Button::setPosition(const Vector2D<int> &pos)
{
    Widget::setPosition(pos);
    Vector2D<int> global = getGlobalPosition();
    m_background.setPosition(global.x, global.y);
}

void Button::setSize(const Vector2D<int> &size)
{
    Widget::setSize(size);
    m_background.setSize(sf::Vector2f(size.x, size.y));
}

void Button::setState(const WidgetState &state)
{
    if (getState() == state)
        return;

    Widget::setState(state);
    if (state == WidgetState::HOVER)
        m_background.setFillColor(sf::Color(255, 0, 0, 95));
    else
        m_background.setFillColor(sf::Color(0, 0, 0, 95));
}
