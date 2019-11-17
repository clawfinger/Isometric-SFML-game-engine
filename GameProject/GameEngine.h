#pragma once
#include <memory>
#include <unordered_map>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include "Events\Observer.h"
#include "SFML\System\Time.hpp"
#include "ECS/Entity.h"

class Window;
class Map;
class SystemBase;
class EventDispatcher;
class DiContainer;
class EntityManager;
class RenderSystem;

class GameEngine :	public Observer
{
public:
	GameEngine(DiContainer* container);
	~GameEngine();
	void draw(std::shared_ptr<Window> window);
	void update(sf::Time deltaTime);
	//void notify(IEvent* event);
	EntityId getActiveCharacter();

	void handlePlayerInput(sf::Event & event);

private:
	void initSystems();

	template<typename T>
	T* getSystem(const std::string& name);

	void handleKeyboardInput(sf::Keyboard::Key key);
	void handleMouseInput(const Vector2i& mouseCoords);

	void handleMapCreatedEvent(IEvent* event);
    void handlePartySlotActiveEvent(IEvent* event);

private:
	EntityId m_activeCharacter;
	std::vector<EntityId> m_characters;
	DiContainer* m_container;
	std::shared_ptr<EventDispatcher> m_eventDispatcher;
	std::shared_ptr<EntityManager> m_entityManager;
	std::shared_ptr<Window> m_window;
	std::shared_ptr<Map> m_map;
	RenderSystem* m_render;
	std::unordered_map<std::string, SystemBase*> m_systems;
};

