#include "Player.h"

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
	m_width = m_player.getLocalBounds().width;
	m_height = m_player.getLocalBounds().height;
	m_pos.x = system.GetWidth() * 0.5f + 50.0f;
	m_pos.y = system.GetHeight() - 380.0f;
	m_player.setPosition(m_pos);
	m_isAlive = true;
	// �浹 ��� Ȱ��ȭ
	this->ActivateCollider(true, this->GetName());
	this->SetCollider(m_pos.x, m_pos.y, m_width, m_height);
}

void Player::OnDraw(sf::RenderWindow& device)
{
	device.draw(m_player);
}

void Player::OnEvent(fz::Event& event)
{
	sf::Event& ev = event.get();
	if (ev.type == ev.KeyPressed && Keyboard::isKeyPressed(Keyboard::Left))
	{
		Move(Direction::Left);
		// event.use();
	}
	if (ev.type == ev.KeyPressed && Keyboard::isKeyPressed(Keyboard::Right))
	{
		Move(Direction::Right);
		// event.use();
	}
}

void Player::OnUpdate(float dt)
{
	this->SetCollider(m_pos.x, m_pos.y, m_width, m_height);
}

void Player::OnCollide(Layer* pLayer, const std::string& className)
{
	
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

bool Player::IsAlive()
{
	return (m_isAlive);
}
