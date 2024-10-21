#pragma once

#include "Core/Core.h"

namespace fz {

	class ImGuiManager
	{
	public:
		static void			Initialize(const sf::Window& window);
		static void			Shutdown();
		static void			Begin();
		static void			End();
		static void			ShowDemo();

		static void			ReleaseDockspace();

	private:
		static bool					s_enableOverviewDockspace;
		static const sf::Window*	s_currWindow;
	};

} // namespace fz
