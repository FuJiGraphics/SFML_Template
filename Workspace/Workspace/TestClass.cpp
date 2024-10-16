#include "TestClass.h"

TestClass::TestClass()
{
}
TestClass::~TestClass()
{
}
void TestClass::OnAttach()
{
	// 배경화면
	m_background.loadFromFile("res/graphics/background.png");
}

void TestClass::OnUpdate(float dt)
{
}

void TestClass::OnDraw(sf::RenderWindow& device)
{
	sf::Sprite sprite(m_background);
	device.draw(sprite);
}
