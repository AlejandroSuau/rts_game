#pragma once

#include "raylib.h"
#include "Types.hpp"
#include "Config.hpp"

#include "Selector.hpp"

#include <array>

struct Units {
    std::array<bool, kMaxTotalUnits> active;
    std::array<bool, kMaxTotalUnits> selected;
    std::array<Rectangle, kMaxTotalUnits> aabb; // Axis-Aligned Bounding Box
};

class Game {
public:
    Game(u32 width, u32 height, std::string_view title);
    void Run();

private:
    u32 width_;
    u32 height_;
    std::string_view title_;

    Units units_;
    
    Selector selector_;

    void Init();
    void Update();
    void Draw();

    void SpawnEntity(const Vector2& coords);
};
