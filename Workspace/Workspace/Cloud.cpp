#include "Cloud.h"

using namespace fz;

sf::FloatRect Cloud::s_wall;

Cloud::Cloud()
	: m_dir(Direction::Default)
	, m_speed(0.0f)
{
	// Empty
}

Cloud::~Cloud()
{
	// Empty
}

void Cloud::OnAttach()
{
	auto& tex = TextureMap::GetTexture("res/graphics/cloud.png");
	m_cloud.setTexture(tex);

	// 바깥 기준 설정
	auto& system = System::GetInstance();
	s_wall.left = (tex.getSize().x) * -1.0f;
	s_wall.width = system.GetWidth() + (tex.getSize().x);

	// 기본 포지션, 방향 설정
	this->ResetPos();
}

void Cloud::OnUpdate(float dt)
{
	Move(dt, m_dir, m_speed);

	if (this->CollideWall())
	{
		this->ResetPos();
	}
}

void Cloud::OnDraw(sf::RenderWindow& device)
{
	device.draw(m_cloud);
}

void Cloud::ResetPos()
{
	// 포지션 설정
	m_dir = GetRandom(0, 1) ? Direction::Left : Direction::Right;
	m_pos.x = (m_dir == Direction::Right) ? s_wall.left : s_wall.width;
	m_pos.y = (float)GetRandom(0, 300);
	m_cloud.setPosition(m_pos);
	if (m_dir == Direction::Left)
		m_cloud.setScale(-1.0f, 1.0f);
	else
		m_cloud.setScale(1.0f, 1.0f);
	// 스피드 설정
	m_speed = (float)GetRandom(100, 200);
}

void Cloud::Move(float dt, Direction dir, float speed)
{
	switch (dir)
	{
		case Direction::Left:
			m_pos.x -= (speed * dt);
			break;
		case Direction::Right:
			m_pos.x += (speed * dt);
			break;
	}
	m_cloud.setPosition(m_pos);
}

bool Cloud::CollideWall()
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


