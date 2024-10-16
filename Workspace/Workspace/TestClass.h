#pragma once

#include <SFML/Graphics.hpp>
#include "Core/System.h"
#include "Core/Layer.h"

class TestClass : public fz::Layer
{
public:
	TestClass();
	~TestClass();

	void OnAttach() override;
	void OnUpdate(float dt) override;
	void OnDraw(sf::RenderWindow& device) override;

private:
	sf::Texture	m_background;
};

ATTACH_LAYER(TestClass)