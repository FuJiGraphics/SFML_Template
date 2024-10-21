#pragma once
#include "VegaEngine/Engine.h"

class Cloud : public fz::Layer
{
public:
	Cloud();
	~Cloud();

	void			OnAttach() override;
	void			OnUpdate(float dt) override;
	void			OnDraw(sf::RenderWindow& device) override;
	std::string		GetName() const override;

	void			ResetPos();
	void			Move(float dt, Direction dir, float speed);
	bool			CollideWall();

private:
	sf::Sprite				m_cloud;
	sf::Vector2f			m_pos;
	Direction				m_dir;
	float					m_speed;
	static sf::FloatRect	s_wall;
};

