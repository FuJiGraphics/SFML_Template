#include "UI.h"
#include "Player.h"

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

	m_state.setFont(m_font);
	m_state.setString("PAUSE!");
	m_state.setCharacterSize(70);
	m_state.setFillColor(sf::Color::White);
	auto& localRectS = m_state.getLocalBounds();
	m_state.setOrigin(localRectS.width * 0.5f, localRectS.height * 0.5f);
	m_state.setPosition(system.GetWidth() * 0.5f, system.GetHeight() * 0.4f);

	m_gameOver.setFont(m_font);
	m_gameOver.setString("GAME OVER!");
	m_gameOver.setCharacterSize(70);
	m_gameOver.setFillColor(sf::Color::White);
	auto& localRectO = m_gameOver.getLocalBounds();
	m_gameOver.setOrigin(localRectO.width * 0.5f, localRectO.height * 0.5f);
	m_gameOver.setPosition(system.GetWidth() * 0.5f, system.GetHeight() * 0.4f);

	m_gameStart.setFont(m_font);
	m_gameStart.setString("PRESS ENTER TO START!");
	m_gameStart.setCharacterSize(70);
	m_gameStart.setFillColor(sf::Color::White);
	auto& localRectG = m_gameStart.getLocalBounds();
	m_gameStart.setOrigin(localRectG.width * 0.5f, localRectG.height * 0.5f);
	m_gameStart.setPosition(system.GetWidth() * 0.5f, system.GetHeight() * 0.4f);

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
	if (fz::System::IsFirstEvent())
		return;

	m_scoreText1.setString("Score = " + std::to_string(g_score));

	sf::Vector2f size = m_timeBar.getSize();
	size.x -= m_timeBarSpeed * dt;
	if (size.x < 0.0f)
	{
		size.x = 0.0f;
		Layer* target = fz::System::FindLayer("Player");
		Player* p = dynamic_cast<Player*>(target);
		if (p != nullptr)
		{
			p->Dead(true);
			m_state.setString("Game Over");
		}
	}
	m_timeBar.setSize(size);
}

void UI::OnUI(sf::RenderWindow& device)
{
	device.draw(m_scoreText1);
	Layer* target = fz::System::FindLayer("Player");
	Player* p = dynamic_cast<Player*>(target);
	if (fz::System::IsFirstEvent())
		device.draw(m_gameStart);
	else if (p != nullptr && !p->IsAlive())
		device.draw(m_gameOver);
	else if (fz::System::IsPaused())
		device.draw(m_state);

	device.draw(m_timeBar);
}

std::string UI::GetName() const
{
	return ("UI");
}

void UI::SetGameOver(bool enabled)
{
	auto& system = fz::System::GetInstance();
	float winWidth = system.GetWidth();
	float winHeight = system.GetHeight();
	if (enabled)
	{
		m_state.setString("Game Over");
		m_state.setPosition(winWidth, winHeight);
	}
	else
	{
		m_state.setString("PRESS ENTER TO START!");
		m_state.setPosition(winWidth * 0.5f, winHeight * 0.5f);
	}
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
