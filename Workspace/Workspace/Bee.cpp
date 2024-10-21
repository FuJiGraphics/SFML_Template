#include "Bee.h"

using namespace fz;

Bee::Bee()
	: m_pos(0.0f, 0.0f)
	, m_dir(Direction::Default)
	, m_speed(0.0f)
{
}

Bee::~Bee()
{
}

void Bee::OnAttach()
{
	Texture::Load("res/graphics/bee.png");
	auto& texture = Texture::Get("res/graphics/bee.png");
	m_bee.setTexture(texture);

	// 바깥 기준 설정
	auto& system = System::GetInstance();
	s_wall.left = (texture.getSize().x) * -1.0f;
	s_wall.width = system.GetWidth() + (texture.getSize().x);

	// 기본 포지션, 방향 설정
	this->ResetPos();
}

void Bee::OnUpdate(float dt)
{
	Move(dt, m_dir, m_speed);

	if (this->CollideWall())
	{
		this->ResetPos();
	}
}

void Bee::OnDraw(sf::RenderTexture& device)
{
	device.draw(m_bee);
}

void Bee::ResetPos()
{
	// 포지션 설정
	m_dir = GetRandom(0, 1) ? Direction::Left : Direction::Right;
	m_pos.x = (m_dir == Direction::Right) ? s_wall.left : s_wall.width;
	m_pos.y = (float)GetRandom(600, 800);
	m_bee.setPosition(m_pos);
	if (m_dir == Direction::Left)
		m_bee.setScale(1.0f, 1.0f);
	else
		m_bee.setScale(-1.0f, 1.0f);
	// 스피드 설정
	m_speed = (float)GetRandom(100, 200);
}

void Bee::Move(float dt, Direction dir, float speed)
{
	static float f = 0.0f;
	f = (f < 6.3f) ? f + (dt) : 0.0f;
	switch (dir)
	{
	case Direction::Left:
		m_pos.x -= (speed * dt);
		m_pos.y += (speed * dt) * sin(f);
		break;
	case Direction::Right:
		m_pos.x += (speed * dt);
		m_pos.y += (speed * dt) * sin(f);
		break;
	}
	m_bee.setPosition(m_pos);
}

bool Bee::CollideWall()
{
	bool result = false;
	switch (m_dir)
	{
	case Direction::Left:
		if (m_pos.x < s_wall.left)
		{
			result = true;
		}
		break;
	case Direction::Right:
		if (m_pos.x > s_wall.width)
		{
			result = true;
		}
		break;
	}

	return (result);
}

std::string Bee::GetName() const
{
	return ("Bee");
}
