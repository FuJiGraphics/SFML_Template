#include "UI.h"
#include "Application.h"
#include "Player.h"

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
	fz::Font::Load("res/fonts/KOMIKAP_.ttf");
	auto& font = fz::Font::Get("res/fonts/KOMIKAP_.ttf");
	m_scoreText.setFont(font);
	m_scoreText.setString("Score = 0");
	m_scoreText.setCharacterSize(100);
	m_scoreText.setFillColor(sf::Color::White);
	m_scoreText.setPosition(10.0f, 10.0f);

	m_state.setFont(font);
	m_state.setString("PAUSE!");
	m_state.setCharacterSize(70);
	m_state.setFillColor(sf::Color::White);
	auto& localRectS = m_state.getLocalBounds();
	m_state.setOrigin(localRectS.width * 0.5f, localRectS.height * 0.5f);
	m_state.setPosition(system.GetWidth() * 0.5f, system.GetHeight() * 0.4f);

	m_gameOver.setFont(font);
	m_gameOver.setString("GAME OVER!");
	m_gameOver.setCharacterSize(70);
	m_gameOver.setFillColor(sf::Color::White);
	auto& localRectO = m_gameOver.getLocalBounds();
	m_gameOver.setOrigin(localRectO.width * 0.5f, localRectO.height * 0.5f);
	m_gameOver.setPosition(system.GetWidth() * 0.5f, system.GetHeight() * 0.4f);

	m_gameStart.setFont(font);
	m_gameStart.setString("PRESS ENTER TO START!");
	m_gameStart.setCharacterSize(70);
	m_gameStart.setFillColor(sf::Color::White);
	auto& localRectG = m_gameStart.getLocalBounds();
	m_gameStart.setOrigin(localRectG.width * 0.5f, localRectG.height * 0.5f);
	m_gameStart.setPosition(system.GetWidth() * 0.5f, system.GetHeight() * 0.4f);

	// 타임 바
	m_timeBarWidth = 400;
	float timeBarHeight = 80;
	m_timeBar.setSize({ m_timeBarWidth, timeBarHeight });
	m_timeBar.setFillColor(sf::Color::Red);
	m_timeBar.setPosition({ 
		(system.GetWidth() * 0.5f) - (m_timeBarWidth * 0.5f),
		(float)system.GetHeight() - (timeBarHeight * 2.0f)
		});
	float timeBarDuration = 3.0f; // 타이머가 0이 되기까지 시간
	float timerBarTime = timeBarDuration;
	m_timeBarSpeed = m_timeBarWidth / timeBarDuration; // 3초마다 삭제됨
	m_score = 0;
}

void UI::OnUpdate(float dt)
{
	m_scoreText.setString("Score = " + std::to_string(m_score));

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

void UI::OnUI(sf::RenderTexture& device)
{
	device.draw(m_scoreText);
	Layer* target = fz::System::FindLayer("Player");
	Player* p = dynamic_cast<Player*>(target);
	target = fz::System::FindLayer("Application");
	Application* a = dynamic_cast<Application*>(target);
	if (a != nullptr && a->IsFirstStart())
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

void UI::AddScore(int add)
{
	m_score += add;
}

void UI::RegainTimebar(float width)
{
	float regain = m_timeBar.getSize().x + width;
	regain = (regain <= m_timeBarWidth) ? regain : m_timeBarWidth;
	m_timeBar.setSize({ regain, m_timeBar.getSize().y });
}

void UI::OnEvent(fz::Event& event)
{
	// Empty
}
