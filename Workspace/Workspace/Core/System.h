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
		static System&	GetInstance();
		static void		Delete();
		static void		AttachLayer(Layer* pLayer);
		static void		AttachOverlay(Layer* pOverlay);

		void			CreateWindow(int width, int height, const char* title);	// 윈도우를 생성한다.
		void			Run();

		// 임시
		sf::RenderWindow&	GetDevice();

	protected:
		System();
		virtual ~System();

	private:
		Window*			m_window;
		LayerArray*		m_layerArray;
		static System*	s_system;
	};

#define ATTACH_LAYER(Layer)							\
	class Generate##Layer							\
	{												\
	public:											\
		Generate##Layer()							\
		{											\
			fz::System::AttachLayer(new (##Layer));	\
		}											\
	};												\
	inline Generate##Layer Object##Layer;		
}
	



