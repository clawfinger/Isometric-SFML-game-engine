#pragma once
#include "ComponentBase.h"
#include "SFML/Graphics/Sprite.hpp"

#include "../../Utils/Meta.h"

class SpriteComponent : public ComponentBase
{
public:
	SpriteComponent();
	~SpriteComponent();
	void create(sf::Texture& texture);
	sf::Sprite& getSprite();
	void setPosition(const sf::Vector2f& position);

private:
	sf::Sprite m_sprite;
};
REGISTER_TYPENAME(SpriteComponent)
