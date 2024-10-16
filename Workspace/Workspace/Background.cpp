#include "Background.h"

using namespace fz;

Background::Background()
{
}
Background::~Background()
{
}
void Background::OnAttach()
{
	// 배경화면
	auto& tex = TextureMap::GetTexture("res/graphics/background.png");
	m_background.setTexture(tex);
}

void Background::OnUpdate(float dt)
{
}

void Background::OnDraw(sf::RenderWindow& device)
{
	device.draw(m_background);
}
