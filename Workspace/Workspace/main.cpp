#include "VegaEngine/Engine.h"
#include "Application.h"

WindowInfo fz::CreateApplication()
{
	return { 1920, 1080, "Game" };
}

void fz::Runtime()
{
	System::AttachLayer(new Application);
}

int main(void)
{
	BeginProcess();

}