#include "Core/System.h"

using namespace fz;

int main(void)
{
	System& system = System::GetInstance();

	system.CreateWindow(1024, 768, "Game");
	system.Run();

	system.Delete();

	return (0);
}