#pragma once
#include "App.h"

class Player : public fz::Layer
{
public:
	Player();
	~Player();

	void	OnAttach() override;
	void	OnDraw(sf::RenderWindow& device) override;
	void	OnEvent(fz::Event& event) override;

	void	Move(Direction dir);

private:
	sf::Sprite		m_player;
	sf::Vector2f	m_pos;
	sf::Vector2f	m_origin;
	bool			m_flip;
};

