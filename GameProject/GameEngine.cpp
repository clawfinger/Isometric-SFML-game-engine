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
#include "ECS\Systems\AnimationSystem.h"
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
	registerCallBack(typeName<MapCreatedEvent>(), std::bind(&GameEngine::handleMapCreatedEvent, this, std::placeholders::_1));
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

//void GameEngine::notify(IEvent * event)
//{
//	if (event->name() == typeName<MapCreatedEvent>())
//	{
//		handleMapCreatedEvent(event);
//	}
//}

EntityId GameEngine::getActiveCharacter()
{
	return m_activeCharacter;
}

void GameEngine::initSystems()
{
	m_render = new RenderSystem(m_container);
	m_systems[typeName<RenderSystem>()] = m_render;

	m_systems[typeName<MovementSystem>()] = new MovementSystem(m_container);
	m_systems[typeName<EntityVisionSystem>()] = new EntityVisionSystem(m_container);
	m_systems[typeName<EntityMapPositionSystem>()] = new EntityMapPositionSystem(m_container);
	m_systems[typeName<AnimationSystem>()] = new AnimationSystem(m_container);
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
			Vector2i coords = Vector2i(event.mouseButton.x, event.mouseButton.y);
			handleMouseInput(coords);
			break;
		}
	}
	}
}

void GameEngine::handleKeyboardInput(sf::Keyboard::Key key)
{
	Vector2f viewMoveVector;
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

void GameEngine::handleMouseInput(const Vector2i& mouseCoords)
{
	sf::Vector2f mouse = m_window->getRenderWindow().mapPixelToCoords(sf::Vector2i(mouseCoords.x, mouseCoords.y));
	Vector2f mapTile = m_map->orthoXYfromIsometricCoords(Vector2f(mouse.x, mouse.y));


	EntityMapPositionSystem* EPSystem = getSystem<EntityMapPositionSystem>(typeName<EntityMapPositionSystem>());
	EntityId entity = EPSystem->getEntityAtCoordinates(Vector2f(mouse.x, mouse.y));
	if (entity != INVALIDID)
	{
		if (std::find(m_characters.begin(), m_characters.end(), entity) != m_characters.end())
		{
			m_activeCharacter = entity;
			//send active char changed event
			return;
		}
	}
	LOG("Active entity: " + std::to_string(m_activeCharacter));

	if (m_map->isWalkable(mapTile))
	{
		m_eventDispatcher->dispatch<SetDestinationForEntityEvent>(m_activeCharacter, mapTile);
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