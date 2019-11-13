#include "Widget.h"
#include "../Utils/Logger.h"

Widget::Widget(const std::string &name, GuiManager *manager, Widget *parent): m_manager(manager), m_nowMoved(false), m_parent(parent),
    m_name(name), m_state(WidgetState::IDLE),
    m_hoverable(false), m_movable(false), m_visible(true)
{
}

Widget::~Widget()
{

}

void Widget::onMousePress(const Vector2D<int> &mousePos)
{
    if (isMovable())
        m_nowMoved = true;
}

void Widget::onMouseRelease(const Vector2D<int> &mousePos)
{
    if (isMovable())
        m_nowMoved = false;
}

void Widget::onMouseHover(const Vector2D<int> &mousePos)
{
    if (isHoverable())
        setState(WidgetState::HOVER);
}

void Widget::onMouseLeave()
{
    if (isHoverable())
        setState(WidgetState::IDLE);
}

void Widget::update(sf::Time deltaTime, const Vector2D<int> &mousePos)
{
    if (m_nowMoved)
    {
        Vector2D<int> delta = mousePos - m_lastMousePos;
        const Vector2D<int>& pos = getPosition();
        setPosition(pos + delta);
    }
    m_lastMousePos = mousePos;
}

void Widget::setPosition(const Vector2D<int> &pos)
{
    if (m_parent != nullptr && !m_parent->isInside(pos))
        LOG("Setting child position outside of parent's bound!");
    m_position = pos;
}

const Vector2D<int>& Widget::getPosition() const
{
    return m_position;
}

void Widget::setSize(const Vector2D<int> &size)
{
    m_size = size;
}

void Widget::adjustContent()
{

}

Vector2D<int> Widget::getGlobalPosition() const
{
    Vector2D<int> position = m_position;
    if (m_parent == nullptr || m_parent == this)
        return position;

    position += m_parent->getGlobalPosition();
    return position;

}

bool Widget::isInside(const Vector2D<int> pos) const
{
    Vector2D<int> position = getGlobalPosition();
    return (pos.x >= position.x && pos.x <= position.x + m_size.x &&
            pos.y >= position.y && pos.y <= position.y + m_size.y);
}

const std::string &Widget::getName() const
{
    return m_name;
}

WidgetState Widget::getState() const
{
    return m_state;
}

void Widget::setState(const WidgetState &state)
{
    m_state = state;
}

bool Widget::isHoverable() const
{
    return m_hoverable;
}

void Widget::setHoverable(bool hoverable)
{
    m_hoverable = hoverable;
}

bool Widget::isMovable() const
{
    return m_movable;
}

void Widget::setMovable(bool movable)
{
    m_movable = movable;
}

bool Widget::isVisible() const
{
    return m_visible;
}

void Widget::setVisible(bool visible)
{
    m_visible = visible;
}

const Vector2D<int> &Widget::getSize() const
{
    return m_size;
}
