#pragma once
#include "Widget.h"
#include "../Utils/Meta.h"

class Button : public Widget
{
public:
    Button(const std::string& m_name, GuiManager *manager, Widget* parent = nullptr);
    virtual ~Button() override = default;
    void onMousePress(const Vector2D<int>& mousePos) override;
    void onMouseRelease(const Vector2D<int>& mousePos) override;
    void onMouseHover(const Vector2D<int>& mousePos) override;
    void onMouseLeave() override;
    void update(sf::Time deltaTime, const Vector2D<int>& mousePos) override;
    void draw(sf::RenderTarget* target) override;
    void setPosition(const Vector2D<int>& pos) override;
    void setSize(const Vector2D<int>& size) override;
    void setState(const WidgetState &state) override;

private:
    sf::RectangleShape m_background;
};
REGISTER_TYPENAME(Button)
