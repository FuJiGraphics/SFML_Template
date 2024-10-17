#pragma once

// Headers
#include <thread>
#include "Core/System.h"
#include "Core/Layer.h"
#include "Core/TextureMap.h"
#include "Core/Collider.h"
#include "Utility/Math.h"

// enums
enum class Direction
{
	Default,
	Left,
	Right,
};

// Dynamic Attach List
void Runtime(fz::System& system);

bool AlivePlayer();

// globals
static int g_score = 0;
