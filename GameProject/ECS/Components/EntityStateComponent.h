#pragma once
#include "ComponentBase.h"
#include "../../Utils/Meta.h"
#include "../../ActorsIds.h"

class EntityStateComponent :public ComponentBase
{
public:
	EntityStateComponent();
	~EntityStateComponent();
	void readData(std::stringstream& l_stream);
	std::string& getState();
	void setState(const std::string& state);

private:
	std::string m_state;
};
REGISTER_TYPENAME(EntityStateComponent)
