#include "App.h"
#include "UI.h"
#include "Background.h"
#include "Cloud.h"
#include "Tree.h"
#include "Bee.h"
#include "Player.h"

void Runtime(fz::System& system)
{
	system.AttachOverlay(new UI);
	system.AttachOverlay(new Background);
	system.AttachOverlay(new Cloud);
	system.AttachOverlay(new Cloud);
	system.AttachOverlay(new Cloud);
	system.AttachLayer(new Bee);
	system.AttachLayer(new Bee);
	system.AttachLayer(new Bee);
	system.AttachLayer(new Player);
	system.AttachLayer(new Tree(system.GetWidth() * 0.5f, 0.0f));
	system.AttachLayer(new Bee);
	system.AttachLayer(new Bee);
}

bool AlivePlayer()
{
	bool result = false;
	fz::Layer* target = fz::System::FindLayer("Player");
	Player* player = dynamic_cast<Player*>(target);
	if (player != nullptr)
	{
		result = player->IsAlive();
	}
	return (result);
}
