#pragma once

#include <slib/types.h>
#include "raylib.h"
#include "Config.hpp"

#include "units/UnitList.hpp"
#include "Selector.hpp"

class Game {
public:
    Game(u32 width, u32 height, std::string_view title);
    void Run();

private:
    u32 width_;
    u32 height_;
    std::string_view title_;

    UnitList units_;
    
    Selector selector_;

    void Init();
    void Update();
    void Draw();

    void SpawnEntity(const Vector2& coords);
};
