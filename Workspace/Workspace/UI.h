#pragma once
#include "App.h"

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
	
	void	OnAttach() override;
	void	OnEvent(fz::Event& event) override;
	void	OnUpdate(float dt) override;
	void	OnUI(sf::RenderWindow& device) override;

private:
	sf::Font			m_font;
	sf::Text			m_scoreText1;
	sf::Text			m_scoreText2;
	sf::RectangleShape	m_timeBar;
	float				m_timeBarSpeed;
};