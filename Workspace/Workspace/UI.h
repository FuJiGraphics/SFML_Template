#pragma once
#include "Engine.h"

// 가지 왼쪽, 오른쪽에 있거나 없거나 (방향 3개)
// 플레이어 나무 기준 왼쪽, 오른쪽
// 플레이어가 살아있을 때만 움직여야함
// 죽었을 때는 비석 이미지로 교체 후 정지 상태
// 재시작 하면 리셋하고 다시 돌아감


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