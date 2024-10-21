#include "Core/stdafx.h"
#include "Window.h"
#include <SFML/Window.hpp>

namespace fz {

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

		if (ImGui::SFML::Init(*m_hwnd))
		{
			// std::cout << "¼º°ø!" << std::endl;
		}
	}

	void Window::Release()
	{
		if (m_hwnd != nullptr)
		{
			ImGui::SFML::Shutdown();
			delete m_hwnd;
			m_hwnd = nullptr;
			m_isOpen = false;
		}
	}

	bool Window::IsOpen()
	{
		return m_isOpen;
	}

	void Window::Event(EventQueue* dst)
	{
		sf::Event ev;
		while (m_hwnd->pollEvent(ev))
		{
			ImGui::SFML::ProcessEvent(*m_hwnd, ev);
			switch (ev.type)
			{
				case sf::Event::Closed:
					m_isOpen = false;
					break;
				case sf::Event::GainedFocus:
					break;
				default:
					if (dst) {
						dst->push(ev);
					} break;
			}
		}
	}

	sf::RenderWindow& Window::GetHandle()
	{
		return (*m_hwnd);
	}

	sf::RenderWindow& Window::GetHandle() const
	{
		return (*m_hwnd);
	}

} // namespace fz