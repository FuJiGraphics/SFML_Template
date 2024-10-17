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

		void			Set(int x, int y, int width, int height);
		const Rect&		Get() const;
		void			Activate(bool flags, const std::string& className, Layer* layer);
		bool			IsActivated();
		bool			IsCollided(const Collider& other);
		Layer*			GetOwner();

	private:
		std::string		m_className;
		Layer*			m_ownerLayer;
		bool			m_isActivate;
		Rect			m_rect;
	};

}
