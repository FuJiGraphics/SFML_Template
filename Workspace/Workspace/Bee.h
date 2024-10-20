#pragma once

#include "VegaEngine/Engine.h"

class Bee : public fz::Layer
{
public:
	Bee();
	~Bee();

	void			OnAttach() override;
	void			OnUpdate(float dt) override;
	void			OnDraw(sf::RenderTexture& device) override;
	std::string		GetName() const override;

	void			ResetPos();
	void			Move(float dt, Direction dir, float speed);
	bool			CollideWall();

private:
	sf::Sprite		m_bee;
	sf::Vector2f	m_pos;
	Direction		m_dir;
	float			m_speed;
	sf::FloatRect	s_wall;
};

