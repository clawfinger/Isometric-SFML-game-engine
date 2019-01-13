#pragma once
#include "ComponentBase.h"
#include "../../Utils/Meta.h"
#include "SFML/System/Vector2.hpp"
#include "SFML/System/Time.hpp"

class PositionComponent : public ComponentBase
{
public:
	PositionComponent();
	~PositionComponent();

	Vector2f& getPosition();
	void setPosition(const Vector2f& position);

	void move(const Vector2f& movement);
	float actorSpeed() const { return m_actorSpeed; }
	void setActorSpeed(float val) { m_actorSpeed = val; }
	void readData(std::stringstream& stream);

private:
	Vector2f m_position;
	float m_actorSpeed;
};
REGISTER_TYPENAME(PositionComponent)