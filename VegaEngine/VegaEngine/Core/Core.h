#pragma once

// standards
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include <functional>
#include <thread>

// graphics
#include <SFML/Graphics.hpp>

// imgui
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "imgui/backends/imgui_impl_win32.h"

namespace fz {

	template <typename T>
	using MemoryPool = std::unordered_map<std::string, T>;

} // namespace fz
