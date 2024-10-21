#include "Player.h"
#include "Branch.h"
#include "UI.h"

using namespace fz;

Player::Player()
{
}

Player::~Player()
{
}

void Player::OnAttach()
{
	System& system = System::GetInstance();
	Texture::Load("res/graphics/player.png");
	auto& texture = Texture::Get("res/graphics/player.png");
	m_player.setTexture(texture);
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
	this->SetColliderDisplayMode(false);
}

void Player::OnDraw(sf::RenderTexture& device)
{
	device.draw(m_player);
}

void Player::OnEvent(fz::Event& event)
{
	if (System::IsPaused())
		return;
	if (!m_isAlive)
		return;
	Layer* target = System::FindLayer("UI");
	UI* u = dynamic_cast<UI*>(target);

	sf::Event& ev = event.get();
	if (ev.type == ev.KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		Move(Direction::Left);
		m_flip = true;
		if (u != nullptr)
		{
			u->RegainTimebar(100.0f);
			u->AddScore(10);
		}
		// event.use();
	}
	if (ev.type == ev.KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		Move(Direction::Right);
		m_flip = false;
		if (u != nullptr)
		{
			u->RegainTimebar(30.0f);
			u->AddScore(10);
		}
		// event.use();
	}
}

void Player::OnUpdate(float dt)
{
	if (System::IsPaused())
		return;
	if (!m_isAlive)
		return;

	this->SetColliderDisplayMode(true);
	this->SetCollider(m_player.getOrigin(), m_player.getGlobalBounds());
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
	fz::Texture::Load("res/graphics/rip.png");
	auto& texture = fz::Texture::Get("res/graphics/rip.png");
	m_player.setTexture(texture);
	m_isAlive = false;
	System::SetPause(true);
}

bool Player::IsAlive()
{
	return (m_isAlive);
}
