#pragma once
#include "App.h"

/* TODO:
	- �÷��̾� �״°� �����ϱ� (�ð� �ʰ� or (HP=0) or �������� �浹)
	- �÷��̾ ���������� ���ϸ� HP �������� ȸ���Ǳ�
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

