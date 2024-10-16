#include "System.h"

System::System()
	: m_window(nullptr)
{
	// Empty
}

System::~System()
{
	if (m_window != nullptr)
	{
		m_window->Release();
		delete m_window;
		m_window = nullptr;
	}
}

void System::CreateWindow(int width, int height, const char* title)
{
	if (m_window != nullptr)
		return;

	m_window = new Window(width, height, title);
	m_window->Create();
}

void System::Run()
{
	while (m_window->IsOpen())
	{
		// 이벤트 루프
		m_window->Event();
	}
}
