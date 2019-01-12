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

}
