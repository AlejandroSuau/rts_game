#pragma once

#include <slib/types.h>
#include <string_view>

/* Engine configuration */

constexpr i32 kTargetFPS = 60;

/* Window setup */

constexpr u32 kWindowWidth = 800;
constexpr u32 kWindowHeight = 600;
constexpr std::string_view kWindowTitle = "RTS Game";


/* Game rules */
constexpr u32 kMaxTotalUnits = 1000;

