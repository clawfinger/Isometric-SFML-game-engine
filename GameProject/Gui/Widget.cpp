#include "Widget.h"

Widget::Widget(const std::string &name, Widget *parent): m_parent(parent), name(name)
{
//    m_rect.setSize(sf::Vector2f(100, 50));
//    m_rect.setFillColor(sf::Color(0, 0, 0, 95));
//    m_rect.setOutlineThickness(2);
//    m_rect.setOutlineColor(sf::Color(sf::Color::Black));
//    m_rect.setPosition(20, 20);
}

Widget::~Widget()
{

}

void Widget::setPosition(const Vector2D<int> &pos)
{
    m_position = pos;
}

void Widget::setSize(const Vector2D<int> &size)
{
    m_size = size;
}

Vector2D<int> Widget::getGlobalPosition()
{
    Vector2D<int> position = m_position;
    if (m_parent == nullptr || m_parent == this)
        return position;

    position += m_parent->getGlobalPosition();
    return position;

}

bool Widget::isInside(const Vector2D<int> pos)
{
    Vector2D<int> position = getGlobalPosition();
    return (pos.x >= position.x && pos.x <= position.x + m_size.x &&
            pos.y >= position.y && pos.y <= position.y + m_size.y);
}
