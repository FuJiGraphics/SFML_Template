#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include <random>

using namespace sf;
using namespace std;

const int g_windowWidth = 1920;
const int g_windowHeight = 1080;
const int g_numOfBee = 100000;

int	GetRandom(int start, int end)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(start, end);
	return (dis(gen)); // ���� ����
}

// ���� �������� �ʺ�� ����
VideoMode vm(g_windowWidth, g_windowHeight);
RenderWindow window(vm, "Timber!!!", sf::Style::Default);

std::vector<float> cloudSpeeds(3);
std::vector<float> cloudDirs(3);

std::vector<float> beeSpeeds(g_numOfBee);
std::vector<float> beeDirs(g_numOfBee);
std::vector<float> beeDirs2(g_numOfBee);

void GenerateObject(
	vector<Sprite>& Objects, 
	vector<float>& speeds, 
	vector<float>& dirs,
	int startY, int endY,
	vector<float>* dirs2 = nullptr)
{
	static Uint32 winX = window.getSize().x;
	static Uint32 winY = window.getSize().y;
	int i = 0;
	for (auto& obj : Objects)
	{
		auto& pos = obj.getPosition();
		if (pos.x > winX + 200.0f || pos.x < -600.0f)
		{
			int newY = GetRandom(startY, endY);
			int ranStart = GetRandom(0, 1);
			int startX = 0.0f;
			if (ranStart)
				startX = -100.0f;
			else
				startX = winX + 100.0f;
			obj.setPosition(startX, newY);
			dirs[i] = (ranStart) ? 1.0f : -1.0f;
			speeds[i] = GetRandom(100, 150);
			if (dirs2 != nullptr)
			{
				(*dirs2)[i] = GetRandom(0, 1) ? 1.0f : -1.0f;
			}
		}
		++i;
	}
}

int main(void)
{
	// ���ȭ��
	Texture texBackground;
	texBackground.loadFromFile("res/graphics/background.png");
	// ����
	Texture texCloud;
	texCloud.loadFromFile("res/graphics/cloud.png");
	// ����
	Texture texTree;
	texTree.loadFromFile("res/graphics/tree.png");
	// ��
	Texture texBee;
	texBee.loadFromFile("res/graphics/bee.png");

	Sprite spriteBackground;
	spriteBackground.setTexture(texBackground);
	spriteBackground.setPosition(0.f, 0.f);

	//������ ����� �ű��.
	const Vector2f newOrigin{ g_windowWidth / 2, g_windowHeight / 2 };
	spriteBackground.setOrigin(newOrigin);
	spriteBackground.setPosition(newOrigin);

	vector<Sprite> spriteClouds(3, Sprite(texCloud));
	for (auto& cloud : spriteClouds)
	{
		cloud.setPosition(-100.f, GetRandom(0, 400));
	}
	for (float& speed : cloudSpeeds)
	{
		speed = GetRandom(100, 250);
	}
	for (float& dir : cloudDirs)
	{
		dir = GetRandom(0, 1) ? 1 : -1;
	}

	Sprite spriteTree(texTree);
	vector<Sprite> spriteBees(g_numOfBee, Sprite(texBee));
	for (float& dir : beeDirs)
	{
		dir = GetRandom(0, 1) ? 1 : -1;
	}
	for (float& dir : beeDirs2)
	{
		dir = GetRandom(0, 1) ? 1 : -1;
	}
	int i = 0;
	for (auto& bee : spriteBees)
	{
		bee.setPosition(-100.f, GetRandom(600, 900));
		bee.setScale(beeDirs[i] * -1.0f, 1.0f);
		++i;
	}
	for (float& speed : beeSpeeds)
	{
		speed = GetRandom(100, 250);
	}


	Vector2f speedBee(100.0f, 0.0f); // v = d / t

	Clock clock;
	while (window.isOpen())
	{
		static double elap = 0;
		Time dt = clock.restart();
		float deltaTime = dt.asSeconds();
		elap += deltaTime;

		// �޼���(�̺�Ʈ) ����
		Event message;
		while (window.pollEvent(message))
		{
			switch (message.type)
			{
			case Event::EventType::Closed:
			{
				window.close();
				break;
			}
			case Event::KeyPressed:
			{
				if (message.key.code == Keyboard::Escape)
					window.close();
				break;
			}
			default:
				break;
			}
		}
		// ������Ʈ ������Ʈ
		// ����
		{
			GenerateObject(spriteClouds, cloudSpeeds, cloudDirs, 0, 300);
			for (int i = 0; i < spriteClouds.size(); ++i)
			{
				auto pos = spriteClouds[i].getPosition();
				pos.x += (cloudSpeeds[i] * deltaTime * cloudDirs[i]);
				spriteClouds[i].setPosition(pos);
				spriteClouds[i].setScale(cloudDirs[i], 1.0f);
			}
		}
		spriteTree.setOrigin(texTree.getSize().x * 0.5f, 0.0f);
		spriteTree.setPosition(g_windowWidth * 0.5f, 0.0f);
		// ��
		{
			GenerateObject(spriteBees, beeSpeeds, beeDirs, 500, 800);
			for (int i = 0; i < spriteBees.size(); ++i)
			{
				sf::Vector2f beePos = spriteBees[i].getPosition();
				beePos.x += beeSpeeds[i] * deltaTime * beeDirs[i];
				beePos.y += (beeSpeeds[i] * deltaTime) * 0.5f * sinf(elap) * beeDirs2[i];
				spriteBees[i].setPosition(beePos);
				spriteBees[i].setScale(beeDirs[i] * -1.0f, 1.0f);
			}
		}

		// ȭ�� �����
		window.clear();
		// ȭ�� �׸���
		window.draw(spriteBackground);
		for (const auto& cloud : spriteClouds)
		{
			window.draw(cloud);
		}
		window.draw(spriteTree);
		for (const auto& bee : spriteBees)
		{
			window.draw(bee);
		}
		// ȭ�� ����
		window.display();
	}

	return (0);
}