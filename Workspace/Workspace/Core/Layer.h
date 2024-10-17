#pragma once

#include "Core.h"
#include "Event.h"

namespace fz {

	class Layer
	{
	public:
		explicit Layer();
		virtual ~Layer();

		virtual void			OnAttach();
		virtual void			OnDetach();
		virtual void			OnEvent(fz::Event& event);
		virtual void			OnUpdate(float dt);
		virtual void			OnDraw(sf::RenderWindow& device);
		virtual void			OnUI(sf::RenderWindow& device);
		virtual std::string		GetName() const;
		static unsigned int		GetCount();

	private:
		static unsigned int		s_numOfLayers;
	};

} // namespace fz