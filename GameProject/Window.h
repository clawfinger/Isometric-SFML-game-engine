#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Utils/Meta.h"

class Window
{
public:
	Window();
	Window(const std::string& windowTitle, const sf::Vector2u& size);
	~Window();

	void beginDraw();
	void endDraw();
	void setup(const std::string& windowTitle, const sf::Vector2u& size);

	bool isDone();
	void setDone();

	bool isFullScreen();
	void toggleFullScreen();

	sf::Vector2u getWindowSize() const;

	void update(sf::Time deltaTime);
	void draw(sf::Drawable& drawable);

	void moveView(sf::Vector2f& movement);
	void resizeView(sf::Vector2f& newSize);

	sf::RenderWindow& getRenderWindow();
	void setViewMoveVector(const sf::Vector2f& moveVector);

private:
	void destroy();
	void create();

private:
	bool m_isDone;
	bool m_isFullScreen;
	sf::RenderWindow m_window;
	std::string m_windowTitle;
	sf::Vector2u m_windowSize;
	sf::View m_mainView;
	sf::Vector2f m_viewMoveVector;
};
REGISTER_TYPENAME(Window)