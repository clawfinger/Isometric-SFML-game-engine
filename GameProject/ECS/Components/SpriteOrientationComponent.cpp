#include <sstream>
#include "../../Utils/Logger.h"

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

sf::IntRect & SpriteOrientationComponent::getRightTextureRect()
{
	if (m_rightTextureRect.height == 0 || m_rightTextureRect.width == 0)
		Logger::instance().log("ERROR: requested empty TextureRect from SpriteOrientationComponent");
	return m_rightTextureRect;
}

void SpriteOrientationComponent::setRightTextureRect(const sf::IntRect & rect)
{
	m_rightTextureRect = rect;
}
