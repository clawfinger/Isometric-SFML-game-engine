#include "Widget.h"

Widget::Widget(const std::string &name, Widget *parent): m_parent(parent), name(name)
{
    m_rect.setSize(sf::Vector2f(100, 50));
    m_rect.setOutlineColor(sf::Color::Red);
    m_rect.setOutlineThickness(5);
    m_rect.setPosition(20, 20);
}

Widget::~Widget()
{

}

void Widget::onMousePress(const Vector2D<int> &mousePos)
{

}

void Widget::onMouseRelease(const Vector2D<int> &mousePos)
{

}

void Widget::onMouseEnter()
{

}

void Widget::onMouseLeave()
{

}

void Widget::update(float deltaTime)
{

}

void Widget::draw(sf::RenderTarget *target)
{
    target->draw(m_rect);
}
