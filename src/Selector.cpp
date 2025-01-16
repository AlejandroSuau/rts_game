#include "Selector.hpp"

void Selector::Deselect() {
    is_selecting_ = false;
}

void Selector::HandleSelection(
    RTSCoords mouse_coords,
    bool is_left_button_down,
    bool is_left_button_released) {
    
    if (is_selecting_) {
        if (is_left_button_released) {
            area_ = RTSRect{};
            is_selecting_ = false;
        } else {
            area_.x = mouse_coords.x;
            area_.y = mouse_coords.y;
            area_.width = starting_point_.x - mouse_coords.x;
            area_.height = starting_point_.y - mouse_coords.y;
        }
    } else if (is_left_button_down) {
        is_selecting_ = true;
        starting_point_ = mouse_coords;
    }
}

const bool Selector::IsSelecting() const {
    return is_selecting_;
}

const RTSRect& Selector::GetArea() const {
    return area_;
}
