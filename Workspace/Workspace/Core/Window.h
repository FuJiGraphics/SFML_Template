#pragma once
#include "Core.h"
#include "Event.h"

class Window
{
public:
	Window(int width, int height, const char* name);
	virtual ~Window();

	void	Create();			// 윈도우를 생성한다.
	void	Release();			// 윈도우를 제거한다.
	bool	IsOpen();			// 윈도우가 현재 화면에 생성되어 있을 경우 true
	void	Event();			// 이벤트 루프

private:
	int	m_width;				// 윈도우의 너비
	int	m_height;				// 윈도우의 높이
	std::string	m_name;			// 윈도우의 이름
	sf::RenderWindow* m_hwnd;	// 핸들
	bool m_isOpen;				// 윈도우 활성화 여부
};

