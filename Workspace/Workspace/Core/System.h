#pragma once
#include "Core.h"
#include "Event.h"
#include "Layer.h"

namespace fz {

	class Window;
	class LayerArray;

	class System
	{
	public:
		static System&		GetInstance();
		static void			Delete();
		static void			AttachLayer(Layer* pLayer);
		static void			AttachOverlay(Layer* pOverlay);

		void				CreateWindow(int width, int height, const char* title);	// 윈도우를 생성한다.
		void				Run();
		int					GetWidth();
		int					GetHeight();

		// 임시
		sf::RenderWindow&	GetDevice();

	protected:
		System();
		virtual ~System();

	private:
		Window*			m_window;
		LayerArray*		m_layerArray;
		int				m_width;
		int				m_height;
		static System*	s_system;
	};

} // namespace fz