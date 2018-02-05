#include "stdafx.h"
#include "window.h"

Window::Window()
{
	setup("Default window", sf::Vector2u(800, 600));
}

Window::Window(const std::string & windowTitle, const sf::Vector2u & size)
{
	setup(windowTitle, size);
}

Window::~Window()
{
	destroy();
}

void Window::beginDraw()
{
	m_window.clear();
}

void Window::endDraw()
{
	m_window.display();
}

bool Window::isDone()
{
	return m_isDone;
}

void Window::setDone()
{
	m_isDone = true;
}

bool Window::isFullScreen()
{
	return m_isFullScreen;
}

sf::Vector2u Window::getWindowSize() const
{
	return m_windowSize;
}

void Window::toggleFullScreen()
{
	m_isFullScreen = !m_isFullScreen;
	destroy();
	create();
}

void Window::draw(sf::Drawable & drawable)
{
	m_window.draw(drawable);
}

void Window::moveView(sf::Vector2f & movement)
{
	m_mainView.move(movement);
	m_window.setView(m_mainView);
}

void Window::resizeView(sf::Vector2f & newSize)
{
	m_mainView.setSize(newSize);
	m_window.setView(m_mainView);
}

sf::RenderWindow& Window::getRenderWindow()
{
	return m_window;
}

void Window::setup(const std::string & windowTitle, const sf::Vector2u & size)
{
	m_windowTitle = windowTitle;
	m_windowSize = size;
	m_isFullScreen = false;
	m_isDone = false;
	m_mainView.setSize(float(size.x), float(size.y));
	m_window.setView(m_mainView);
	create();
}

void Window::destroy()
{
	m_window.close();
}

void Window::create()
{
	unsigned int style;
	if (m_isFullScreen)
		style = sf::Style::Fullscreen;
	else
		style = sf::Style::Default;
	//uniform initialisation of sf::VideoMode
	m_window.create({ m_windowSize.x, m_windowSize.y, 32 }, m_windowTitle, style);
	m_window.setFramerateLimit(60);
}

//void Window::update()
//{
//	sf::Event event;
//	while (m_window.pollEvent(event))
//	{
//		if (event.type == sf::Event::Closed)
//			m_isDone = true;
//		else if (event.type == sf::Event::KeyPressed &&
//			event.key.code == sf::Keyboard::F12)
//		{
//			toggleFullScreen();
//		}
//	}
//}
