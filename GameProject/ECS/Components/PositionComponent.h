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

	sf::Vector2f& getPosition();
	void setPosition(const sf::Vector2f& position);

	void move(const sf::Vector2f& movement);
	float actorSpeed() const { return m_actorSpeed; }
	void setActorSpeed(float val) { m_actorSpeed = val; }
	void readData(std::stringstream& stream);
	void setPauseTime(sf::Time value) { m_pauseTime = value; }
	sf::Time& getPauseTime(){ return m_pauseTime; }

private:
	sf::Vector2f m_position;
	float m_actorSpeed;
	sf::Time m_pauseTime;
};
REGISTER_TYPENAME(PositionComponent)