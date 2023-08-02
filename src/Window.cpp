#include "Window.h"

Window::Window()
	:	m_renderWindow(sf::VideoMode(WIDTH, HEIGHT), "6 Colors") {}

sf::RenderWindow& Window::getRenderedWindow()
{
	return m_renderWindow;
}
