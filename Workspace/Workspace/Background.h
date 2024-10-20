#pragma once

#include "VegaEngine/Engine.h"

class Background : public fz::Layer
{
public:
	Background();
	~Background();

	void OnAttach() override;
	void OnUpdate(float dt) override;
	void OnDraw(sf::RenderWindow& device) override;
	std::string		GetName() const override;

private:
	sf::Sprite	m_background;
};
