#include "stdafx.h"
#include <sstream>
#include "SpriteOrientationComponent.h"


SpriteOrientationComponent::SpriteOrientationComponent(): ComponentBase(typeName<SpriteOrientationComponent>()), m_orientation(SpriteOrientation::right)
{
}


SpriteOrientationComponent::~SpriteOrientationComponent()
{
}

void SpriteOrientationComponent::readData(std::stringstream& stream)
{
	stream >> m_rightTextureRect.left;
	stream >> m_rightTextureRect.top;
	stream >> m_rightTextureRect.width;
	stream >> m_rightTextureRect.height;
}
