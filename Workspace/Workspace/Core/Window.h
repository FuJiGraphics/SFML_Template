#pragma once
#include "Core.h"
#include "Event.h"

class Window
{
public:
	Window(int width, int height, const char* name);
	virtual ~Window();

	void	Create();			// �����츦 �����Ѵ�.
	void	Release();			// �����츦 �����Ѵ�.
	bool	IsOpen();			// �����찡 ���� ȭ�鿡 �����Ǿ� ���� ��� true
	void	Event();			// �̺�Ʈ ����

private:
	int	m_width;				// �������� �ʺ�
	int	m_height;				// �������� ����
	std::string	m_name;			// �������� �̸�
	sf::RenderWindow* m_hwnd;	// �ڵ�
	bool m_isOpen;				// ������ Ȱ��ȭ ����
};

