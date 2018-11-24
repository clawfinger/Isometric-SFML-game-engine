#include <sstream>
#include "VisionComponent.h"


VisionComponent::VisionComponent(): ComponentBase(typeName<VisionComponent>()), m_vision(4)
{

}


VisionComponent::~VisionComponent()
{
}

void VisionComponent::readData(std::stringstream & stream)
{
	stream >> m_vision;
}
