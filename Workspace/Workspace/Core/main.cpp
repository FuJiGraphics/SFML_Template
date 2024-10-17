#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#include "System.h"
#include "App.h"

using namespace fz;

void Process()
{
	System& system = System::GetInstance();
	system.CreateWindow(1920, 1080, "Game");
	Runtime(system);
	system.Run();
	system.Delete();
}

int main(void)
{
	Process();
	
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	_CrtDumpMemoryLeaks();

	return (0);
}