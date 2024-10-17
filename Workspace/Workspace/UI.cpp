#include "UI.h"

using namespace sf;

UI::UI()
{
}

UI::~UI()
{
}

void UI::OnAttach()
{
	auto& system = fz::System::GetInstance();

	// 폰트
	m_font.loadFromFile("res/fonts/KOMIKAP_.ttf");
	m_scoreText1.setFont(m_font);
	m_scoreText1.setString("Score = 0");
	m_scoreText1.setCharacterSize(100);
	m_scoreText1.setFillColor(sf::Color::White);
	m_scoreText1.setPosition(10.0f, 10.0f);

	m_scoreText2.setFont(m_font);
	m_scoreText2.setString("PRESS ENTER TO START!");
	m_scoreText2.setCharacterSize(70);
	m_scoreText2.setFillColor(sf::Color::White);
	auto& localRect = m_scoreText2.getLocalBounds();
	m_scoreText2.setOrigin(localRect.width * 0.5f, localRect.height * 0.5f);
	m_scoreText2.setPosition(system.GetWidth() * 0.5f, system.GetHeight() * 0.5f);

	// 타임 바
	float timeBarWidth = 400;
	float timeBarHeight = 80;
	m_timeBar.setSize({ timeBarWidth, timeBarHeight });
	m_timeBar.setFillColor(sf::Color::Red);
	m_timeBar.setPosition({ 
		(system.GetWidth() * 0.5f) - (timeBarWidth * 0.5f), 
		(float)system.GetHeight() - (timeBarHeight * 2.0f)
		});
	float timeBarDuration = 3.0f; // 타이머가 0이 되기까지 시간
	float timerBarTime = timeBarDuration;
	m_timeBarSpeed = timeBarWidth / timeBarDuration; // 3초마다 삭제됨
}

void UI::OnUpdate(float dt)
{
	m_scoreText1.setString("Score = " + std::to_string(g_score));

	sf::Vector2f size = m_timeBar.getSize();
	size.x -= m_timeBarSpeed * dt;
	if (size.x < 0.0f)
	{
		size.x = 0.0f;
		// Game Over;
	}
	m_timeBar.setSize(size);
}

void UI::OnUI(sf::RenderWindow& device)
{
	device.draw(m_scoreText1);
	device.draw(m_scoreText2);
	device.draw(m_timeBar);
}

void UI::OnEvent(fz::Event& event)
{
	sf::Event& ev = event.get();
	if (ev.type == ev.KeyPressed && Keyboard::isKeyPressed(Keyboard::Num1))
	{
		g_score += 10;
		event.use();
	}
	if (ev.type == ev.KeyPressed && Keyboard::isKeyPressed(Keyboard::Num2))
	{
		g_score -= 10;
		event.use();
	}
}
