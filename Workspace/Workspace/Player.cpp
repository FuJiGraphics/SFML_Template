#include "Player.h"
#include "Branch.h"

using namespace fz;
using namespace sf;

Player::Player()
{
}

Player::~Player()
{
}

void Player::OnAttach()
{
	System& system = System::GetInstance();
	auto& tex = TextureMap::GetTexture("res/graphics/player.png");
	m_player.setTexture(tex);
	m_player.setOrigin(-150.0f, 0.0f);
	m_origin = m_player.getOrigin();
	m_width = m_player.getLocalBounds().width;
	m_height = m_player.getLocalBounds().height;
	m_pos.x = system.GetWidth() * 0.5f + 50.0f;
	m_pos.y = system.GetHeight() - 380.0f;
	m_player.setPosition(m_pos);
	m_isAlive = true;
	m_flip = false;
	// 충돌 기능 활성화
	this->ActivateCollider(true, this->GetName());
	this->SetCollider(m_origin, m_player.getLocalBounds());
	this->SetColliderDisplayMode(true);
}

void Player::OnDraw(sf::RenderWindow& device)
{
	device.draw(m_player);
}

void Player::OnEvent(fz::Event& event)
{
	if (!m_isAlive)
		return;

	sf::Event& ev = event.get();
	if (ev.type == ev.KeyPressed && Keyboard::isKeyPressed(Keyboard::Left))
	{
		Move(Direction::Left);
		m_flip = true;
		// event.use();
	}
	if (ev.type == ev.KeyPressed && Keyboard::isKeyPressed(Keyboard::Right))
	{
		Move(Direction::Right);
		m_flip = false;
		// event.use();
	}
}

void Player::OnUpdate(float dt)
{
	if (!m_isAlive)
		return;
	
	auto& origin = m_player.getOrigin();
	auto& pos = m_player.getGlobalBounds();
	sf::FloatRect tRec;
	tRec.left = pos.left + origin.x;
	tRec.top = pos.top + origin.y;
	tRec.width = pos.width;
	tRec.height = pos.height;
	this->SetCollider(m_origin, tRec);
}

void Player::OnCollide(Layer* pLayer, const std::string& className)
{
	if (className == "Branch")
	{
		Branch* target = dynamic_cast<Branch*>(pLayer);
		if (target)
		{
			target->Destroy(true);
			this->Dead(true);
		}
	}
}

std::string Player::GetName() const
{
	return ("Player");
}

void Player::Move(Direction dir)
{
	if (!m_isAlive)
		return;

	System& system = System::GetInstance();
	if (dir == Direction::Left)
	{
		m_player.setScale(-1.0f, 1.0f);
		m_pos.x = system.GetWidth() * 0.5f - 50.0f;
		m_player.setPosition(m_pos);
	}
	else if (dir == Direction::Right)
	{
		m_player.setScale(1.0f, 1.0f);
		m_pos.x = system.GetWidth() * 0.5f + 50.0f;
		m_player.setPosition(m_pos);
	}
}

void Player::Dead(bool enabled)
{
	System& system = System::GetInstance();
	auto& tex = TextureMap::GetTexture("res/graphics/rip.png");
	m_player.setTexture(tex);
	m_isAlive = false;
}

bool Player::IsAlive()
{
	return (m_isAlive);
}
