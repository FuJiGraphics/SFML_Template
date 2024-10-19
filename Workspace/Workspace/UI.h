#pragma once
#include "Engine.h"

// ���� ����, �����ʿ� �ְų� ���ų� (���� 3��)
// �÷��̾� ���� ���� ����, ������
// �÷��̾ ������� ���� ����������
// �׾��� ���� �� �̹����� ��ü �� ���� ����
// ����� �ϸ� �����ϰ� �ٽ� ���ư�


class UI : public fz::Layer
{
public:
	UI();
	~UI();
	
	void			OnAttach() override;
	void			OnEvent(fz::Event& event) override;
	void			OnUpdate(float dt) override;
	void			OnUI(sf::RenderWindow& device) override;
	std::string		GetName() const;

	void			RegainTimebar(float width);

private:
	sf::Text			m_score;
	sf::Text			m_gameStart;
	sf::Text			m_gameOver;
	sf::Text			m_state;
	sf::RectangleShape	m_timeBar;
	float				m_timeBarSpeed;
	float				m_timeBarWidth;
};