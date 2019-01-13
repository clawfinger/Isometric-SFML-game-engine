#pragma once
#include "ComponentBase.h"
#include "SFML/Graphics/Sprite.hpp"

#include "../../Utils/Meta.h"
#include "SFML/Graphics/Rect.hpp"

class SpriteComponent : public ComponentBase
{
public:
	SpriteComponent();
	~SpriteComponent();
	void create(sf::Texture& texture);
	void create(sf::Texture & texture, const sf::IntRect & textureRect);
	sf::Sprite& getSprite();
	void setPosition(const Vector2f& position);
	Vector2f& getSize();
	void readData(std::stringstream& stream);
private:
	sf::Sprite m_sprite;
	Vector2f m_size;
};
REGISTER_TYPENAME(SpriteComponent)
