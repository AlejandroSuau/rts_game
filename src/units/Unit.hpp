#pragma once

#include "raylib.h"

struct Unit {
    bool is_active {false};
    bool is_selected {false};
    Rectangle aabb {}; // Axis-Aligned Bounding Box
};