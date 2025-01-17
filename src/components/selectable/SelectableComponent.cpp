#include "components/selectable/SelectableComponent.hpp"

void SelectableComponent::OnSelect() {
    is_selected_ = true;
}

void SelectableComponent::OnDeselect() {
    is_selected_ = false;
}

bool SelectableComponent::IsSelected() const {
    return is_selected_;
}

void SelectableComponent::DrawSelectionIndicator(const RTSRect& bounds) const {
    DrawRectangleLines(
        static_cast<int>(bounds.x) - 2,
        static_cast<int>(bounds.y) - 2,
        static_cast<int>(bounds.width) + 4,
        static_cast<int>(bounds.height) + 4, GREEN);
}
