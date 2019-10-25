#include "Layout.h"

Layout::Layout(const std::string &name, Widget *parent):
    Widget(name, parent)
{
    m_background.setFillColor(sf::Color(0, 0, 0, 95));
    m_background.setOutlineThickness(2);
    m_background.setOutlineColor(sf::Color(sf::Color::Black));
}

void Layout::onMousePress(const Vector2D<int> &mousePos)
{

}

void Layout::onMouseRelease(const Vector2D<int> &mousePos)
{

}

void Layout::draw(sf::RenderTarget *target)
{
    target->draw(m_background);
}

void Layout::setPosition(const Vector2D<int> &pos)
{
    Widget::setPosition(pos);
    Vector2D<int> global = getGlobalPosition();
    m_background.setPosition(global.x, global.y);
}

void Layout::setSize(const Vector2D<int> &size)
{
    Widget::setSize(size);
    m_background.setSize(sf::Vector2f(size.x, size.y));
}
