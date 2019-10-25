#pragma once
#include <vector>
#include <string>
#include "SFML/Graphics.hpp"
#include "../Utils/Vector2D.h"
#include "../Utils/Meta.h"

enum class WidgetState
{
    IDLE = 0,
    HOVER,
    PRESSED,
    MOVED
};

class Widget
{
public:
    Widget(const std::string& name, Widget* parent = nullptr);
    virtual ~Widget();
    virtual void onMousePress(const Vector2D<int>& mousePos) = 0;
    virtual void onMouseRelease(const Vector2D<int>& mousePos) = 0;
    virtual void onMouseEnter() = 0;
    virtual void onMouseLeave() = 0;
    virtual void update(sf::Time deltaTime, const Vector2D<int>& mousePos) = 0;
    virtual void draw(sf::RenderTarget* target) = 0;
    virtual void setPosition(const Vector2D<int>& pos);
    const Vector2D<int> &getPosition() const;
    virtual void setSize(const Vector2D<int>& size);
    Vector2D<int> getGlobalPosition() const;
    bool isInside(const Vector2D<int> pos) const;

    WidgetState getState() const;
    virtual void setState(const WidgetState &state);

    bool isHoverable() const;
    void setHoverable(bool hoverable);

    bool isMovable() const;
    void setMovable(bool movable);

    bool isVisible() const;
    void setVisible(bool visible);

protected:
    bool m_nowMoved;

private:
    Widget* m_parent;
    std::string name;
    Vector2D<int> m_position;
    Vector2D<int> m_size;
    WidgetState m_state;
    bool m_hoverable;
    bool m_movable;
    bool m_visible;
};
REGISTER_TYPENAME(Widget)
