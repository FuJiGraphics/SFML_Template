#include "stdafx.h"
#include "Framework/Framework.h"

using namespace sf;

#define FRAMEWORK Framework::Instance()

int main(void)
{
	FRAMEWORK.Init(1024, 768, "SFML Framework");
	FRAMEWORK.Do();
	FRAMEWORK.Release();

	return 0;
}