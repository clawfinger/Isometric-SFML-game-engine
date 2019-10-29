#pragma once
#include "Widget.h"

class Button : public Widget
{
public:
    Button(const std::string& name, Widget* parent = nullptr);
    virtual ~Button() = default;
    void onMousePress(const Vector2D<int>& mousePos);
    void onMouseRelease(const Vector2D<int>& mousePos);
    void onMouseHover(const Vector2D<int>& mousePos);
    void onMouseLeave();
    void update(sf::Time deltaTime, const Vector2D<int>& mousePos);
    void draw(sf::RenderTarget* target);
    void setPosition(const Vector2D<int>& pos);
    void setSize(const Vector2D<int>& size);
};
