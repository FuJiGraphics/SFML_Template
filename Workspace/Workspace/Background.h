#pragma once

#include "App.h"

class Background : public fz::Layer
{
public:
	Background();
	~Background();

	void OnAttach() override;
	void OnUpdate(float dt) override;
	void OnDraw(sf::RenderWindow& device) override;

private:
	sf::Sprite	m_background;
};
