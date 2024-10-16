#pragma once
#include "Core.h"
#include "EventQueue.h"

namespace fz {

	class Window
	{
	public:
		Window(int width, int height, const char* name);
		virtual ~Window();

		void				Create();
		void				Release();
		bool				IsOpen();
		void				Event(EventQueue* dst);
		sf::RenderWindow&	GetHandle();

	private:
		int					m_width;	// �������� �ʺ�
		int					m_height;	// �������� ����
		std::string			m_name;		// �������� �̸�
		sf::RenderWindow*	m_hwnd;		// �ڵ�
		bool				m_isOpen;	// ������ Ȱ��ȭ ����
	};

}

