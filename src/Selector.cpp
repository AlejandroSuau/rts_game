#include "Selector.hpp"

#include <cmath>

void Selector::Deselect() {
    is_selecting_ = false;
}

void Selector::HandleSelection(
    const Vector2& mouse_coords,
    bool is_left_button_down,
    bool is_left_button_released) {
    
    if (is_selecting_) {
        if (is_left_button_released) {
            area_ = Rectangle{};
            is_selecting_ = false;
        } else {
            area_.x = mouse_coords.x;
            area_.y = mouse_coords.y;
            area_.width = starting_point_.x - mouse_coords.x;
            area_.height = starting_point_.y - mouse_coords.y;

            /**
             * TODO: handle this better way.
             * Width and height can not be negative. Otherwise collisions works bad.
             */
            if (area_.width < 0.f) {
                area_.x = starting_point_.x;
                area_.width = abs(area_.width);
            }
            if (area_.height < 0.f) {
                area_.y = starting_point_.y;
                area_.height = abs(area_.height);
            }
        }
    } else if (is_left_button_down) {
        is_selecting_ = true;
        starting_point_ = mouse_coords;
    }
}

bool Selector::IsSelecting() const {
    return is_selecting_;
}

const Rectangle& Selector::GetArea() const {
    return area_;
}
