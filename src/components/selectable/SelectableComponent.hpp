#pragma once

#include "Types.hpp"

#include "components/selectable/ISelectable.hpp"

class SelectableComponent final : public ISelectable {
public:
    void OnSelect() override;
    void OnDeselect() override;
    bool IsSelected() const override;

    void DrawSelectionIndicator(const RTSRect& bounds) const;

private:
    bool is_selected_;
};
