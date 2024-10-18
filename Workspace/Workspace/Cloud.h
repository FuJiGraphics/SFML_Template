#pragma once

#include "App.h"

class Cloud : public fz::Layer
{
public:
	Cloud();
	~Cloud();

	void OnAttach() override;
	void OnUpdate(float dt) override;
	void OnDraw(sf::RenderWindow& device) override;

	void ResetPos();
	void Move(float dt, Direction dir, float speed);
	bool CollideWall();
	std::string		GetName() const override;

private:
	sf::Sprite				m_cloud;
	sf::Vector2f			m_pos;
	Direction				m_dir;
	float					m_speed;
	static sf::FloatRect	s_wall;
};

