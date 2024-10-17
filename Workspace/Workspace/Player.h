#pragma once
#include "App.h"

/* TODO:
	- 플레이어 죽는거 구현하기 (시간 초과 or (HP=0) or 나뭇가지 충돌)
	- 플레이어가 나뭇가지를 피하면 HP 게이지가 회복되기
*/

class Player : public fz::Layer
{
public:
	Player();
	~Player();

	void			OnAttach() override;
	void			OnDraw(sf::RenderWindow& device) override;
	void			OnEvent(fz::Event& event) override;
	void			OnUpdate(float dt) override;
	void			OnCollide(Layer* pLayer, const std::string& className) override;
	std::string		GetName() const override;

	void			Move(Direction dir);
	bool			IsAlive();

private:
	sf::Sprite		m_player;
	sf::Vector2f	m_pos;
	int				m_width;
	int				m_height;
	sf::Vector2f	m_origin;
	bool			m_flip;
	bool			m_isAlive;
};

