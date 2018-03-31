#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"

class PathFollower;
class Window;

class Actor : public Entity
{
public:
	Actor();
	~Actor();
	float getActorSpeed();
	void setActorSpeed(float speed);
	void draw(Window* window);
	PathFollower* pathComponent();
private:
	PathFollower* m_PathComponent;
	float m_actorSpeed;
};

