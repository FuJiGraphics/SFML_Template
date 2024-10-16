#pragma once
#include "Core.h"
#include "Window.h"
#include "Event.h"

class System
{
public:
	System();
	virtual ~System();

	void	CreateWindow(int width, int height, const char* title);	// 윈도우를 생성한다.
	void	Run();

private:
	Window*	m_window;
};