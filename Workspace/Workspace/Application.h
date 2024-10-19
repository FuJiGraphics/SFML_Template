#pragma once

// Headers
#include "Engine.h"

class Application : public fz::Layer
{
public:
	void OnAttach() override;
	void OnEvent(fz::Event& event) override;
	std::string	GetName() const override;

public:
	bool	IsFirstStart() const;

private:
	bool	m_IsFirstStart;
};

