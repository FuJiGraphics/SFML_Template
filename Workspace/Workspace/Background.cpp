#include "stdafx.h"
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
	Texture::Load("res/graphics/background.png");
	auto& texture = Texture::Get("res/graphics/background.png");
	m_background.setTexture(texture);
}

void Background::OnUpdate(float dt)
{
}

void Background::OnDraw(sf::RenderTexture& device)
{
	device.draw(m_background);
}

std::string Background::GetName() const
{
	return ("Background");
}
