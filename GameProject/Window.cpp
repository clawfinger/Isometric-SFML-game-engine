#include "Window.h"

static const int ZOOM_FACTOR_LIMIT = 5;

Window::Window(): m_zoomFactor(0), m_viewSpeed(600.0)
{
	setup("Default window", sf::Vector2u(800, 600));
}

Window::Window(const std::string & windowTitle, const sf::Vector2u & size) :
    m_zoomFactor(0), m_viewSpeed(300.0)
{
	setup(windowTitle, size);
}

Window::~Window()
{
	destroy();
}

void Window::beginDraw()
{
	m_window.clear(sf::Color(119, 136, 153, 255));
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

void Window::zoomInView()
{
    if (m_zoomFactor >= ZOOM_FACTOR_LIMIT)
        return;

    resizeView(0.95);
    m_zoomFactor++;
}

void Window::zoomOutView()
{
    if (m_zoomFactor <= -ZOOM_FACTOR_LIMIT * 2)
        return;

    resizeView(1.05);
    m_zoomFactor--;
}

void Window::moveView(const Vector2f& movement)
{
	m_mainView.move(movement.x, movement.y);
    m_window.setView(m_mainView);
}

void Window::moveViewToPoint(int x, int y)
{
    m_mainView.setCenter(x, y);
    m_window.setView(m_mainView);
}

void Window::update(sf::Time deltaTime)
{
	moveView(m_viewMoveVector * deltaTime.asSeconds() * m_viewSpeed);
}

void Window::resizeView(const Vector2f & newSize)
{
	m_mainView.setSize(newSize.x, newSize.y);
	m_window.setView(m_mainView);
}

void Window::resizeView(float factor)
{
    m_mainView.zoom(factor);
    m_window.setView(m_mainView);
}



sf::View & Window::getView()
{
	return m_mainView;
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

void Window::setViewMoveVector(const Vector2f & moveVector)
{
	m_viewMoveVector = moveVector;
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
        style = sf::Style::Close ;
	//uniform initialisation of sf::VideoMode
    m_window.create({ m_windowSize.x, m_windowSize.y, 32 }, m_windowTitle, style, sf::ContextSettings(0, 0, 8));
	//m_window.setVerticalSyncEnabled(true);
}
