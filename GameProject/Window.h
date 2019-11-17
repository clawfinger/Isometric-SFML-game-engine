#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Utils/Meta.h"
#include "Utils/Vector2D.h"

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

	void moveView(const Vector2f& movement);
	void resizeView(const Vector2f& newSize);
	sf::View& getView();

	sf::RenderWindow& getRenderWindow();
	void setViewMoveVector(const Vector2f& moveVector);

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
	Vector2f m_viewMoveVector;
	float m_viewSpeed;
};
REGISTER_TYPENAME(Window)
