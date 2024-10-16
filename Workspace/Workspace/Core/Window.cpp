#include "Window.h"
#include <SFML/Window.hpp>

Window::Window(int width, int height, const char* name)
	: m_width(width)
	, m_height(height)
	, m_name(name)
	, m_hwnd(nullptr)
	, m_isOpen(false)
{
	// Empty
}

Window::~Window()
{
	this->Release();
}

void Window::Create()
{
	if (m_hwnd != nullptr)
		return;

	sf::VideoMode mode(m_width, m_height);
	m_hwnd = new sf::RenderWindow(mode, m_name);

	m_isOpen = true;
}

void Window::Release()
{
	if (m_hwnd != nullptr)
	{
		delete m_hwnd;
		m_hwnd = nullptr;
		m_isOpen = false;
	}
}

bool Window::IsOpen()
{
	return m_isOpen;
}

void Window::Event()
{
	sf::Event ev;
	while (m_hwnd->pollEvent(ev))
	{
		switch (ev.type)
		{
		case sf::Event::Closed:
			m_isOpen = false;
			break;
		}
	}
}
