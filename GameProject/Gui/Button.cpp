#include "Button.h"

Button::Button(const std::string &name, Widget *parent): Widget(name, parent)
{

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

}

void Button::setPosition(const Vector2D<int> &pos)
{
    Widget::setPosition(pos);
    Vector2D<int> global = getGlobalPosition();
}

void Button::setSize(const Vector2D<int> &size)
{

}
