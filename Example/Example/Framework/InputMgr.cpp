#include "stdafx.h"
#include "InputMgr.h"

std::list<sf::Keyboard::Key> InputMgr::downList;
std::list<sf::Keyboard::Key> InputMgr::heldList;
std::list<sf::Keyboard::Key> InputMgr::upList;

void InputMgr::Clear()
{
	downList.clear();
	upList.clear();
}

void InputMgr::UpdateEvent(const sf::Event& ev)
{
	switch (ev.type)
	{
	case sf::Event::KeyPressed:
		if (std::find(heldList.begin(), heldList.end(), ev.key.code) == heldList.end())
		{
			heldList.push_back(ev.key.code);
			downList.push_back(ev.key.code);
		}
		break;
	case sf::Event::KeyReleased:
		heldList.remove(ev.key.code);
		upList.push_back(ev.key.code);
		break;
	}
}

bool InputMgr::GetKeyDown(sf::Keyboard::Key key)
{
	return std::find(downList.begin(), downList.end(), key) != downList.end();;
}

bool InputMgr::GetKey(sf::Keyboard::Key key)
{
	return std::find(heldList.begin(), heldList.end(), key) != heldList.end();
}

bool InputMgr::GetKeyUp(sf::Keyboard::Key key)
{
	return std::find(upList.begin(), upList.end(), key) != upList.end();
}