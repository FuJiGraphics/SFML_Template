#include "Branch.h"
#include "Player.h"

using namespace fz;

Branch::Branch(const sf::Vector2f& origin, const sf::Vector2f& pos, bool flipX, bool flipY)
	: m_origin(origin)
	, m_pos(pos)
	, m_flip{ flipX, flipY }
	, m_width(0)
	, m_height(0)
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
	Texture::Load("res/graphics/branch.png");
	auto& texture = Texture::Get("res/graphics/branch.png");
	m_branch.setTexture(texture);
	m_branch.setOrigin(m_origin);
	m_branch.setPosition(m_pos);
	if (m_flip[0])
		m_branch.setScale(-1.0f, 1.0f);
	m_width = m_branch.getLocalBounds().width;
	m_height = m_branch.getLocalBounds().height;
	this->ActivateCollider(true, this->GetName());

	this->SetCollider(m_branch.getOrigin(), m_branch.getGlobalBounds());
	this->SetColliderDisplayMode(true);
}

void Branch::OnDraw(sf::RenderTexture& device)
{
	if (m_Destroyed)
		return;
	
	device.draw(m_branch);
}

void Branch::OnUpdate(float dt)
{
	if (m_Destroyed)
		return;

	this->SetCollider(m_branch.getOrigin(), m_branch.getGlobalBounds());
}

void Branch::OnCollide(Layer* pLayer, const std::string& className)
{
	if (this->GetName() == className)
		return;

	if (className == "Player")
	{
		this->Kill(pLayer, className);
	}
}

std::string Branch::GetName() const
{
	return ("Branch");
}

void Branch::Move(float d)
{
	m_pos.x = m_pos.x;
	m_pos.y = m_pos.y + d;
	m_branch.setPosition(m_pos);
	
	// ¶¥¿¡ ´êÀ» ½Ã ÆÄ±«
	if (m_pos.y > 840.0f)
	{
		m_Destroyed = true;
	}
}

bool Branch::IsDestroyed()
{
	return (m_Destroyed);
}

void Branch::Destroy(bool enabled)
{
	m_Destroyed = enabled;
}

void Branch::Kill(Layer* player, const std::string& className)
{
	if (className == "Player")
	{
		Player* p = dynamic_cast<Player*>(player);
		if (p != nullptr)
		{
			p->Dead(true);
			this->Destroy(true);
		}
	}
}
