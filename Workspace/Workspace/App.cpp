#include "App.h"
#include "Background.h"
#include "Cloud.h"

void Runtime(fz::System& system)
{
	system.AttachOverlay(new Background);
	system.AttachOverlay(new Cloud);
	system.AttachOverlay(new Cloud);
	system.AttachOverlay(new Cloud);
}
