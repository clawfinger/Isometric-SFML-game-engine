#pragma once
#include "ComponentBase.h"
#include "../../Utils/Meta.h"
#include "SFML/System/Vector2.hpp"

class PositionComponent : public ComponentBase
{
public:
	PositionComponent();
	~PositionComponent();

	sf::Vector2f getPosition();
	void setPosition(const sf::Vector2f& position);

	void move(const sf::Vector2f& movement);
	float actorSpeed() const { return m_actorSpeed; }
	void setActorSpeed(float val) { m_actorSpeed = val; }
private:
	sf::Vector2f m_position;
	float m_actorSpeed;
};
REGISTER_TYPENAME(PositionComponent)