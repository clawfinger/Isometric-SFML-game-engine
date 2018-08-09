#include "stdafx.h"
#include "GameEngine.h"
#include "Events/Events.h"
#include "Utils/Logger.h"
#include "DiContainer\DiContainer.h"
#include "Events\EventDispatcher.h"
#include "ECS\EntityManager.h"
#include "ECS\Systems\MovementSystem.h"
#include "ECS\Systems\RenderSystem.h"
#include "ECS\Systems\SpriteOrientationSystem.h"
#include "ECS\Systems\EntityVisionSystem.h"
#include "ECS\Systems\EntityMapPositionSystem.h"
#include "Map.h"
#include "Window.h"

GameEngine::GameEngine(DiContainer* container): m_container(container)
{
	initSystems();
	m_eventDispatcher = m_container->get<EventDispatcher>();
	m_entityManager = m_container->get<EntityManager>();
	m_map = m_container->get<Map>();
	m_window = m_container->get<Window>();
	m_characters = m_entityManager->loadCharacters();

	if (!m_characters.empty())
		m_activeCharacter = m_characters[0];

	m_eventDispatcher->subscribe(typeName<MapCreatedEvent>(), this);
}


GameEngine::~GameEngine()
{
}

void GameEngine::draw(std::shared_ptr<Window> window)
{
	m_render->draw(window);
}

void GameEngine::update(sf::Time deltaTime)
{
	for (auto& system : m_systems)
	{
		system.second->update(deltaTime);
	}
}

void GameEngine::notify(IEvent * event)
{
	if (event->name() == typeName<MapCreatedEvent>())
	{
		handleMapCreatedEvent(event);
	}
}

EntityId GameEngine::getActiveCharacter()
{
	return m_activeCharacter;
}

void GameEngine::initSystems()
{
	m_render = new RenderSystem(m_container);
	m_systems[typeName<RenderSystem>()] = m_render;

	m_systems[typeName<MovementSystem>()] = new MovementSystem(m_container);
	m_systems[typeName<SpriteOrientationSystem>()] = new SpriteOrientationSystem(m_container); 
	m_systems[typeName<EntityVisionSystem>()] = new EntityVisionSystem(m_container);
	m_systems[typeName<EntityMapPositionSystem>()] = new EntityMapPositionSystem(m_container);
}

void GameEngine::handleMapCreatedEvent(IEvent * event)
{
	MapCreatedEvent *currentEvent = dynamic_cast<MapCreatedEvent *>(event);
	if (nullptr != currentEvent)
	{
		m_entityManager->spawnCharacters();
		m_entityManager->spawnEnemy(currentEvent->mapType);
	}
}

void GameEngine::handlePlayerInput(sf::Event& event)
{
	switch (event.type)
	{
	case sf::Event::KeyReleased:
	case sf::Event::KeyPressed:
		handleKeyboardInput(event.key.code);
		break;
	case sf::Event::MouseButtonPressed:
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			sf::Vector2i coords = sf::Vector2i(event.mouseButton.x, event.mouseButton.y);
			handleMouseInput(coords);
			break;
		}
	}
	}
}

void GameEngine::handleKeyboardInput(sf::Keyboard::Key key)
{
	sf::Vector2f viewMoveVector;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		viewMoveVector.y = -1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		viewMoveVector.y = 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		viewMoveVector.x = -1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		viewMoveVector.x = 1;

	m_window->setViewMoveVector(viewMoveVector);
}

void GameEngine::handleMouseInput(sf::Vector2i mouseCoords)
{
	sf::Vector2f mouse = m_window->getRenderWindow().mapPixelToCoords(mouseCoords);
	int mapIndex = m_map->mapIndexFromWindow(mouse.x, mouse.y);
	sf::Vector2i mapXY = m_map->XYfromWindow(mouse);

	EntityMapPositionSystem* EPSystem = getSystem<EntityMapPositionSystem>(typeName<EntityMapPositionSystem>());
	EntityId entity = EPSystem->getEntityAtMapXY(mapXY.x, mapXY.y);
	if (!(entity < 0))
	{
		if (std::find(m_characters.begin(), m_characters.end(), entity) != m_characters.end())
		{
			m_activeCharacter = entity;
			//send active char changed event
			return;
		}
	}
	if (m_map->isWalkable(m_map->XYfromLinear(mapIndex)))
	{
		IEvent* tileClicked = new SetDestinationForEntityEvent(getActiveCharacter(), mapIndex);
		m_eventDispatcher->dispatch(tileClicked);
	}
}

	template<typename T>
	T* GameEngine::getSystem(const std::string& name)
	{
		auto iterator = m_systems.find(name);
		if (iterator != m_systems.end())
		{
			return dynamic_cast<T*>(iterator->second);
		}
		else
			return nullptr;
	}