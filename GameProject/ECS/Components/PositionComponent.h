#pragma once
#include "ComponentBase.h"
#include "../../Utils/Meta.h"
#include "SFML/System/Vector2.hpp"

enum class SpriteOrientation
{
	left,
	right
};

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
	void readData(std::stringstream& stream);
	SpriteOrientation orientation() const { return m_orientation; }
	void setOrientation(SpriteOrientation val) { m_orientation = val; }
private:
	sf::Vector2f m_position;
	float m_actorSpeed;
	SpriteOrientation m_orientation;
};
REGISTER_TYPENAME(PositionComponent)