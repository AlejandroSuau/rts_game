#pragma once

#include "raylib.h"

class Selector {
public:
    void Deselect();
    void HandleSelection(
        const Vector2& mouse_coords,
        bool is_left_button_down,
        bool is_left_button_released);

    bool IsSelecting() const;
    const Rectangle& GetArea() const;

private:
    bool is_selecting_;
    Vector2 starting_point_;
    Rectangle area_;
};
