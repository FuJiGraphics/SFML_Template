#include "Application.h"
#include "UI.h"
#include "Background.h"
#include "Cloud.h"
#include "Tree.h"
#include "Bee.h"
#include "Player.h"

using namespace fz;

WindowInfo fz::CreateApplication()
{
	return { 1920, 1080, "Game" };
}

void fz::Runtime()
{
	System::AttachLayer(new Application);
}

void Application::OnAttach()
{
	auto& system = System::GetInstance();
	System::AttachOverlay(new UI);
	System::AttachOverlay(new Background);
	System::AttachOverlay(new Cloud);
	System::AttachOverlay(new Cloud);
	System::AttachOverlay(new Cloud);
	System::AttachLayer(new Bee);
	System::AttachLayer(new Bee);
	System::AttachLayer(new Bee);
	System::AttachLayer(new Player);
	System::AttachLayer(new Tree(system.GetWidth() * 0.5f, 0.0f));
	System::AttachLayer(new Bee);
	System::AttachLayer(new Bee);
	System::SetPause(true);
	m_IsFirstStart = true;
}

void Application::OnEvent(fz::Event& event)
{
	auto& ev = event.get();
	switch (ev.type)
	{
		case sf::Event::KeyPressed:
		{
			if (ev.key.code == sf::Keyboard::Return)
			{
				if (m_IsFirstStart)
				{
					m_IsFirstStart = false;
					System::SetPause(false);
				}
				else
				{
					Layer* target = System::FindLayer("Player");
					Player* p = dynamic_cast<Player*>(target);
					if (p != nullptr && !p->IsAlive())
					{
						System::SetReset(true);
						event.use();
					}
				}
			}
			if (ev.key.code == sf::Keyboard::Escape)
			{
				if (!m_IsFirstStart)
				{
					static bool isPause = true;
					System::SetPause(isPause);
					isPause = (isPause) ? false : true;
				}
			}
		}
	}
}

std::string Application::GetName() const
{
	return ("Application");
}

bool Application::IsFirstStart() const
{
	return (m_IsFirstStart);
}

