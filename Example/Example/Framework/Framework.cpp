#include "stdafx.h"
#include "Framework.h"
#include "InputMgr.h"
#include "SpriteGo.h"

void Framework::Init(int width, int height, const std::string& name)
{
	window.create(sf::VideoMode(width, height), name);
}

void Framework::Do()
{
	SpriteGo go("res/graphics/background.png");
	go.Init();
	go.Release();

	while (window.isOpen())
	{
		sf::Time dt = clock.restart();
		realDeltaTime = dt.asSeconds();
		deltaTime *= timeScale;
		realTime += realDeltaTime;
		time += deltaTime;

		// �̺�Ʈ ����
		InputMgr::Clear();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			InputMgr::UpdateEvent(event);
		}

		// ������Ʈ


		// �׸���
		window.clear();
		go.Draw(window);
		window.display();
	}

	go.Release();
}

void Framework::Release()
{
}
