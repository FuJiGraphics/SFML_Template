#pragma once
#include "VegaEngine/Engine.h"

class Branch : public fz::Layer
{
public:
	Branch(const sf::Vector2f& origin, const sf::Vector2f& pos, bool flipX = false, bool flipY = false);
	~Branch();

	void			OnAttach() override;
	void			OnDraw(sf::RenderTexture& device) override;
	void			OnUpdate(float dt) override;
	void			OnCollide(Layer* pLayer, const std::string& className) override;
	std::string		GetName() const override;

	void			Move(float d);
	bool			IsDestroyed();
	void			Destroy(bool enabled);
	void			Kill(Layer* player, const std::string& className);

private:
	sf::Sprite		m_branch;
	sf::Vector2f	m_pos;
	sf::Vector2f	m_origin;
	int				m_width;
	int				m_height;
	bool			m_flip[2];
	bool			m_Destroyed;
};
