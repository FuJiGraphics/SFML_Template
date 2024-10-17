#include "Branch.h"

using namespace fz;

Branch::Branch(const sf::Vector2f& origin, const sf::Vector2f& pos, bool flipX, bool flipY)
	: m_origin(origin)
	, m_pos(pos)
	, m_flip{ flipX, flipY }
	, m_Destroyed(false)
{
	// Empty
}

Branch::~Branch()
{
	// Empty
}

void Branch::OnAttach()
{
	auto& tex = TextureMap::GetTexture("res/graphics/branch.png");
	m_branch.setTexture(tex);
	m_branch.setOrigin(m_origin);
	m_branch.setPosition(m_pos);
	if (m_flip[0])
		m_branch.setScale(-1.0f, 1.0f);
}

void Branch::OnDraw(sf::RenderWindow& device)
{
	device.draw(m_branch);
}

void Branch::Move(float d)
{
	m_pos.x = m_pos.x;
	m_pos.y = m_pos.y + d;
	m_branch.setPosition(m_pos);
	
	// ¶¥¿¡ ´êÀ» ½Ã ÆÄ±«
	if (m_pos.y > 800)
	{
		m_Destroyed = true;
	}
}

bool Branch::IsDestroyed()
{
	return (m_Destroyed);
}
