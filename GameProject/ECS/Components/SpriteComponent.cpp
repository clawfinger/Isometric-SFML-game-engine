#include "stdafx.h"
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
}
