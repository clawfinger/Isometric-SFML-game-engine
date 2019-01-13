#pragma once
#include "ComponentBase.h"
#include "../../Utils/Meta.h"

enum class EntityState
{
	idle,
	moving
};


class EntityStateComponent :public ComponentBase
{
public:
	EntityStateComponent();
	~EntityStateComponent();
	void readData(std::stringstream& l_stream);
	EntityState getState();
	void setState(EntityState state);

private:
	EntityState m_state;
};
REGISTER_TYPENAME(EntityStateComponent)
