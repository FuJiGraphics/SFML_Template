#include "Collider.h"

namespace fz {

	Collider::Collider()
		: m_isActivate(false)
		, m_className("")
		, m_ownerLayer(nullptr)
		, m_rect({0, 0, 0, 0})
	{
		// Empty
	}

	Collider::~Collider()
	{
		// Empty
	}

	void Collider::Set(int x, int y, int width, int height)
	{
		m_rect = { x, y, width, height };
	}

	const Rect& Collider::Get() const
	{
		return (m_rect);
	}

	void Collider::Activate(bool flags, const std::string& className, Layer* layer)
	{
		m_isActivate = flags;
		m_className = className;
		m_ownerLayer = layer;
	}

	bool Collider::IsActivated()
	{
		return (m_isActivate);
	}

	bool Collider::IsCollided(const Collider& other)
	{
		if (this == &other)
			return (false);
		const Rect& srcRec = other.Get();
		int srcX = srcRec.x;
		int srcY = srcRec.y;
		int srcW = srcRec.x + srcRec.w;
		int srcH = srcRec.y + srcRec.h;
		int dstX = m_rect.x;
		int dstY = m_rect.y;
		int dstW = dstX + m_rect.w;
		int dstH = dstY + m_rect.h;
		if (dstW < srcX || dstX > srcW)
			return (false);
		if (dstH < srcY || dstY > srcH)
			return (false);
		if (m_ownerLayer)
			m_ownerLayer->OnCollide(other.m_ownerLayer, other.m_ownerLayer->GetName());
		return (true);
	}

	Layer* Collider::GetOwner()
	{
		return (m_ownerLayer);
	}

} // namespace fz