#pragma once

#include "Types.hpp"

class Entity {
public:
    Entity(const RTSRect& rect);
    void Draw();

private:
    RTSRect rect_;
};