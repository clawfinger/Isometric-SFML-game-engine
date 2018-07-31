#pragma once
#include "ComponentBase.h"
#include "../../Utils/Meta.h"

class VisionComponent : public ComponentBase
{
public:
	VisionComponent();
	~VisionComponent();
	void readData(std::stringstream& stream);

private:
	int m_vision;
};
REGISTER_TYPENAME(VisionComponent)
