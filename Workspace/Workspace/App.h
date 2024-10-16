#pragma once

// Headers
#include "Core/System.h"
#include "Core/Layer.h"
#include "Core/TextureMap.h"
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
