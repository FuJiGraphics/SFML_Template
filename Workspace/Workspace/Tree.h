#pragma once
#include "VegaEngine/Engine.h"
#include "Branch.h"

class Tree : public fz::Layer
{
public:
	Tree(int posX, int posY);
	~Tree();

	void			OnAttach() override;
	void			OnDraw(sf::RenderWindow& device) override;
	void			OnEvent(fz::Event& event) override;
	std::string		GetName() const;

	bool			CutOff();

private:
	sf::Sprite				m_tree;
	sf::Vector2f			m_pos;
	std::vector<Branch*>	m_Branches;
};

