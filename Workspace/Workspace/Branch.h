#pragma once
#include "App.h"

class Branch : public fz::Layer
{
public:
	Branch(const sf::Vector2f& origin, const sf::Vector2f& pos, bool flipX = false, bool flipY = false);
	~Branch();

	void	OnAttach() override;
	void	OnDraw(sf::RenderWindow& device) override;

	void	Move(float d);
	bool	IsDestroyed();

private:
	sf::Sprite		m_branch;
	sf::Vector2f	m_pos;
	sf::Vector2f	m_origin;
	bool			m_flip[2];
	bool			m_Destroyed;
};
