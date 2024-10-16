#pragma once
#include "Core.h"
#include "Window.h"
#include "Event.h"

class System
{
public:
	System();
	virtual ~System();

	void	CreateWindow(int width, int height, const char* title);	// �����츦 �����Ѵ�.
	void	Run();

private:
	Window*	m_window;
};