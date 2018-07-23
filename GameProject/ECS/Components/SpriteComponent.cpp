#include "stdafx.h"
#include <sstream>
#include "SpriteComponent.h"


SpriteComponent::SpriteComponent() : ComponentBase(typeName<SpriteComponent>())
{
}


SpriteComponent::~SpriteComponent()
{
}

void SpriteComponent::create(sf::Texture & texture)
{
	m_sprite.setTexture(texture);
}

void SpriteComponent::create(sf::Texture & texture, const sf::IntRect& textureRect)
{
	m_sprite.setTexture(texture);
	m_sprite.setTextureRect(textureRect);
}

sf::Sprite & SpriteComponent::getSprite()
{
	return m_sprite;
}

void SpriteComponent::setPosition(const sf::Vector2f & position)
{
	m_sprite.setPosition(position.x, position.y);
}

void SpriteComponent::readData(std::stringstream & stream)
{
	int x = 0;
	int y = 0;
	stream >> x >> y;
	m_sprite.setOrigin(float(x), float(y));
	sf::IntRect textureRect;
	stream >> textureRect.left;
	stream >> textureRect.top;
	stream >> textureRect.width;
	stream >> textureRect.height;
	m_sprite.setTextureRect(textureRect);
}
