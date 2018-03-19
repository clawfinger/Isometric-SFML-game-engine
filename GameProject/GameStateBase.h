#pragma once
namespace sf
{
	class Time;
	class Event;
}

class GameStateBase
{
public:
	virtual void update(sf::Time deltaTime) = 0;
	virtual void render() = 0;
	virtual void handlePlayerInput(sf::Event&) = 0;
	virtual ~GameStateBase() {};
};

