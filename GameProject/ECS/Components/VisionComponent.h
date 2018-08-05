#pragma once
#include "ComponentBase.h"
#include "../../Utils/Meta.h"

class VisionComponent : public ComponentBase
{
public:
	VisionComponent();
	~VisionComponent();
	void readData(std::stringstream& stream);

	int getVision() const { return m_vision; }
	void setVision(int val) { m_vision = val; }

private:
	int m_vision;
};
REGISTER_TYPENAME(VisionComponent)
