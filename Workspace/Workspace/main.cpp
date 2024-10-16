#include "Core/System.h"
#include "App.h"

using namespace fz;

int main(void)
{
	System& system = System::GetInstance();

	system.CreateWindow(1920, 1080, "Game");
	Runtime(system);
	system.Run();
	system.Delete();

	return (0);
}