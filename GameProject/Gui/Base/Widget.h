#pragma once
#include <vector>
#include <string>
#include "SFML/Graphics.hpp"
#include "../../Utils/Vector2D.h"
#include "../../Utils/Meta.h"

class GuiEventController;

enum class WidgetState
{
    IDLE = 0,
    HOVER
};

class Widget
{
public:
    Widget(const std::string& m_name, const GuiEventController& controller,
           Widget* parent = nullptr);
    virtual ~Widget();
    virtual void onMousePress(const Vector2D<int>& mousePos);
    virtual void onMouseRelease(const Vector2D<int>& mousePos);
    virtual void onMouseHover(const Vector2D<int>& mousePos);
    virtual void onMouseLeave();
    virtual void update(sf::Time deltaTime, const Vector2D<int>& mousePos);
    virtual void draw(sf::RenderTarget* target) = 0;
    virtual void setPosition(const Vector2D<int>& pos);
    const Vector2D<int> &getPosition() const;
    virtual void setSize(const Vector2D<int>& size);
    virtual void adjustContent();
    const Vector2D<int>& getSize() const;

    Vector2D<int> getGlobalPosition() const;
    bool isInside(const Vector2D<int> pos) const;
    const std::string& getName() const;
    void updatePosition() const;

    WidgetState getState() const;
    virtual void setState(const WidgetState &state);

    bool isHoverable() const;
    void setHoverable(bool hoverable);

    bool isMovable() const;
    void setMovable(bool movable);

    bool isVisible() const;
    void setVisible(bool visible);

protected:
    const GuiEventController& m_controller;

private:
    Widget* m_parent;
    std::string m_name;
    Vector2D<int> m_position;
    Vector2D<int> m_lastMousePos;
    Vector2D<int> m_size;
    WidgetState m_state;
    bool m_nowMoved;
    bool m_hoverable;
    bool m_movable;
    bool m_visible;
};
REGISTER_TYPENAME(Widget)
