#include "stdafx.h"
#include "SpriteGo.h"

SpriteGo::SpriteGo(const std::string& textureID)
	: texID(textureID)
{
}

void SpriteGo::SetPosition(const sf::Vector2f& pos)
{
}

void SpriteGo::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

void SpriteGo::Init()
{
	fz::Texture::Load(texID);
	sprite.setTexture(fz::Texture::Get(texID));
}

void SpriteGo::Release()
{
}

void SpriteGo::Reset()
{
}
