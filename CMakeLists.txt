cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 14)
project(GameProject LANGUAGES CXX)

find_package(SFML REQUIRED COMPONENTS main graphics window system)

set(HEADERS
    GameProject/Window.h
    GameProject/Game.h
    GameProject/GameEngine.h
    GameProject/LevelInfo.h
    GameProject/TextureManager.h
    GameProject/GameState.h
    GameProject/Map.h
    GameProject/ActorsIds.h
    GameProject/Command/Commands.h
    GameProject/Command/CommandExecutors.h
    GameProject/Command/CommandDispatcher.h
    GameProject/DiContainer/DiContainer.h
    GameProject/DiContainer/Factory.h
    GameProject/DiContainer/ConstructingFunctions.h
    GameProject/ECS/Entity.h
    GameProject/ECS/EntityContainer.h
    GameProject/ECS/EntityManager.h
    GameProject/ECS/Components/AIControlledComponent.h
    GameProject/ECS/Components/AnimationComponent.h
    GameProject/ECS/Components/ComponentBase.h
    GameProject/ECS/Components/EntityStateComponent.h
    GameProject/ECS/Components/PathComponent.h
    GameProject/ECS/Components/PositionComponent.h
    GameProject/ECS/Components/SpriteComponent.h
    GameProject/ECS/Components/SpriteOrientationComponent.h
    GameProject/ECS/Components/VisionComponent.h
    GameProject/ECS/Systems/AnimationSystem.h
    GameProject/ECS/Systems/EntityMapPositionSystem.h
    GameProject/ECS/Systems/EntityVisionSystem.h
    GameProject/ECS/Systems/MovementSystem.h
    GameProject/ECS/Systems/RenderSystem.h
    GameProject/ECS/Systems/SpriteOrientationSystem.h
    GameProject/ECS/Systems/SystemBase.h
    GameProject/ECS/Systems/VisualNotificationSystem.h
    GameProject/Events/EventDispatcher.h
    GameProject/Events/Events.h
    GameProject/Events/Observer.h
    GameProject/Events/Subscription.h
    GameProject/Gui/Base/GuiManager.h
    GameProject/Gui/Base/Widget.h
    GameProject/Gui/Base/Layout.h
    GameProject/Gui/Base/Button.h
    GameProject/Gui/Base/GuiEventController.h
    GameProject/State/GameLevelState.h
    GameProject/State/GameStateBase.h
    GameProject/State/GameStateManager.h
    GameProject/Utils/Logger.h
    GameProject/Utils/Meta.h
    GameProject/Utils/StructSerialization.h
    GameProject/Utils/utility.h
    )

set(SOURCES
    GameProject/Utils/Vector2D.h

    GameProject/Window.cpp
    GameProject/Game.cpp
    GameProject/GameProject.cpp
    GameProject/GameEngine.cpp
    GameProject/TextureManager.cpp
    GameProject/Map.cpp
    GameProject/Command/Commands.cpp
    GameProject/Command/CommandExecutors.cpp
    GameProject/Command/CommandDispatcher.cpp
    GameProject/ECS/EntityContainer.cpp
    GameProject/ECS/EntityManager.cpp
    GameProject/ECS/Components/AIControlledComponent.cpp
    GameProject/ECS/Components/AnimationComponent.cpp
    GameProject/ECS/Components/EntityStateComponent.cpp
    GameProject/ECS/Components/PathComponent.cpp
    GameProject/ECS/Components/PositionComponent.cpp
    GameProject/ECS/Components/SpriteComponent.cpp
    GameProject/ECS/Components/SpriteOrientationComponent.cpp
    GameProject/ECS/Components/VisionComponent.cpp
    GameProject/ECS/Systems/AnimationSystem.cpp
    GameProject/ECS/Systems/EntityMapPositionSystem.cpp
    GameProject/ECS/Systems/EntityVisionSystem.cpp
    GameProject/ECS/Systems/MovementSystem.cpp
    GameProject/ECS/Systems/RenderSystem.cpp
    GameProject/ECS/Systems/SpriteOrientationSystem.cpp
    GameProject/ECS/Systems/SystemBase.cpp
    GameProject/ECS/Systems/VisualNotificationSystem.cpp
    GameProject/Events/EventDispatcher.cpp
    GameProject/Events/Events.cpp
    GameProject/Events/Subscription.cpp
    GameProject/Gui/Base/GuiManager.cpp
    GameProject/Gui/Base/Widget.cpp
    GameProject/Gui/Base/Layout.cpp
    GameProject/Gui/Base/Button.cpp
    GameProject/Gui/Base/GuiEventController.cpp
    GameProject/State/GameLevelState.cpp
    GameProject/State/GameStateManager.cpp
    GameProject/Utils/Logger.cpp
    GameProject/Utils/utility.cpp
    )

add_executable(GameProject
    ${HEADERS}
    ${SOURCES}
    )

target_link_libraries(GameProject sfml-graphics sfml-main)
include_directories(${SFML_INCLUDE_DIR})
