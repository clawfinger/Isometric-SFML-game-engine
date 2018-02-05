#pragma once
#include <SFML/Graphics.hpp>
#include <string>
class Window
{
public:
	Window();
	Window(const std::string& windowTitle, const sf::Vector2u& size);
	~Window();

	void beginDraw();
	void endDraw();

	//void update();
	bool isDone();
	void setDone();
	bool isFullScreen();
	sf::Vector2u getWindowSize() const;
	void toggleFullScreen();
	void draw(sf::Drawable& drawable);
	void moveView(sf::Vector2f& movement);
	void resizeView(sf::Vector2f& newSize);
	sf::RenderWindow& getRenderWindow();
	void setup(const std::string& windowTitle, const sf::Vector2u& size);

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
};
