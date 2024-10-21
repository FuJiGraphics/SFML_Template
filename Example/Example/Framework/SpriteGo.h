#pragma once
#include "GameObject.h"

class SpriteGo : public GameObject
{
public:
	explicit SpriteGo() = default;
	explicit SpriteGo(const std::string& textureID);
	~SpriteGo() = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void SetPosition(const sf::Vector2f& pos) override;
	void Draw(sf::RenderWindow& window) override;

protected:
	sf::Sprite sprite;
	std::string texID;
};

