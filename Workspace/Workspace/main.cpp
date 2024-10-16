#include "Core/System.h"

int main(void)
{
	System system;

	system.CreateWindow(1024, 768, "Game");
	system.Run();

	return (0);
}