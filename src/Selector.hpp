#pragma once

#include "Types.hpp"

class Selector {
public:
    void Deselect();
    void HandleSelection(
        RTSCoords mouse_coords,
        bool is_left_button_down,
        bool is_left_button_released);

    const bool IsSelecting() const;
    const RTSRect& GetArea() const;

private:
    bool is_selecting_;
    RTSCoords starting_point_;
    RTSRect area_;
};
