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
		static void			DetachLayer(Layer* ppLayer);
		static void			DetachOverlay(Layer* ppOverlay);
		static Layer*		FindLayer(const std::string& className);
		static void			ExitProgram();
		static void			SetPause(bool enabled);
		static void			SetReset(bool enabled);
		static bool			GetResetStatus();
		static bool			IsPaused();
		static bool			IsFirstEvent();

		void				CreateWindow(int width, int height, const char* title);	// 윈도우를 생성한다.
		void				Run();
		void				Reset();
		int					GetWidth();
		int					GetHeight();

		// 임시
		sf::RenderWindow&	GetDevice();

	protected:
		System();
		virtual ~System();

		void				ReleaseWindow();
		void				CreateLayerArray();
		void				ReleaseLayerArray();

	private:
		Window*			m_window;
		LayerArray*		m_layerArray;
		int				m_width;
		int				m_height;
		bool			m_isPause;
		bool			m_isPlaying;
		bool			m_isReset;
		bool			m_isFirstStart;
		static float	s_timeScale;
	};

} // namespace fz