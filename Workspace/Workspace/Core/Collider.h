#pragma once
#include "Core.h"
#include "Layer.h"

namespace fz {
	
	struct Rect
	{
		int x, y;
		int w, h;
	};

	class Collider
	{
	public:
		Collider();
		virtual ~Collider();

		void				Set(const sf::Vector2f& origin, const sf::FloatRect& rect, const sf::Vector2f& scale);
		const Rect&			Get() const;
		void				Activate(bool flags, const std::string& className, Layer* layer);
		void				SetDisplay(bool enabled);
		void				SetOutlineColor(const sf::Color& color);
		bool				IsDisplay() const;
		sf::RectangleShape&	GetBox();
		bool				IsActivated();
		bool				IsCollided(Collider& other);
		Layer*				GetOwner();

	private:
		sf::RectangleShape	m_Box;
		std::string			m_className;
		Layer*				m_ownerLayer;
		bool				m_isActivate;
		bool				m_IsDisplay;
		Rect				m_rect;
	};

}
