#pragma once
#include <vector>
#include <memory>
#include <string>
#include "SFML/Graphics.hpp"
#include "../Utils/Vector2D.h"

class Widget
{
public:
    Widget(const std::string& name, Widget* parent = nullptr);
    virtual ~Widget();
    virtual void onMousePress(const Vector2D<int>& mousePos);
    virtual void onMouseRelease(const Vector2D<int>& mousePos);
    virtual void onMouseEnter();
    virtual void onMouseLeave();
    virtual void update(float deltaTime);
    virtual void draw(sf::RenderTarget* target);

private:
    Widget* m_parent;
    std::string name;
    Vector2D<int> m_position;

    sf::Text m_text;
    sf::Sprite m_skin;
    sf::RectangleShape m_rect;
};
