#pragma once
#include <unordered_map>
#include "Widget.h"
#include "SFML/Graphics.hpp"
#include "../Utils/Meta.h"

class Layout : public Widget
{
public:
    Layout(const std::string& m_name, GuiManager *manager, Widget* parent = nullptr);
    void onMousePress(const Vector2D<int>& mousePos) override;
    void onMouseRelease(const Vector2D<int>& mousePos) override;
    void onMouseHover(const Vector2D<int>& mousePos) override;
    void onMouseLeave() override;
    void update(sf::Time deltaTime, const Vector2D<int>& mousePos) override;
    void draw(sf::RenderTarget* target) override;
    void setPosition(const Vector2D<int>& pos) override;
    void setSize(const Vector2D<int>& size) override;
    void setState(const WidgetState &state) override;
    void addWidget(Widget* child);

private:
    sf::RectangleShape m_background;
    std::unordered_map<std::string, Widget*> m_children;
};
REGISTER_TYPENAME(Layout)
