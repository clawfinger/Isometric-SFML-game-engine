#pragma once
#include "SFML/Graphics/Rect.hpp"
#include "ComponentBase.h"
#include "../../Utils/Meta.h"


enum class SpriteOrientation
{
	left,
	right
};

class SpriteOrientationComponent :	public ComponentBase
{
public:
	SpriteOrientationComponent();
	~SpriteOrientationComponent();
	SpriteOrientation orientation() const { return m_orientation; }
	void setOrientation(SpriteOrientation val) { m_orientation = val; }
	void readData(std::stringstream& stream);
	sf::IntRect& getRightTextureRect() { return m_rightTextureRect; }
private:
	SpriteOrientation m_orientation;
	sf::IntRect m_rightTextureRect;
};
REGISTER_TYPENAME(SpriteOrientationComponent)
