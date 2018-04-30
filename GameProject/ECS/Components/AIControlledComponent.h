#pragma once
#include "../../Utils/Meta.h"
#include "ComponentBase.h"

class AIControlledComponent : public ComponentBase
{
public:
	AIControlledComponent() :ComponentBase(typeName<AIControlledComponent>()) {}
	void readData(std::stringstream& l_stream) {}
};
REGISTER_TYPENAME(AIControlledComponent)