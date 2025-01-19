#include "units/UnitList.hpp"

#include <algorithm>
#include <ranges>

UnitList::UnitList() : units_{} {}

bool UnitList::AddUnit(Rectangle aabb) {
    auto did_exist_slot = [](const auto& unit) { return !unit.is_active; };
    auto it = std::find_if(units_.begin(), units_.end(), did_exist_slot);
    const bool did_find_slot = (it != units_.end());
    if (did_find_slot) {
        it->is_active = true;
        it->aabb = aabb;
        TraceLog(LOG_INFO, "New unit: {%.2f, %.2f, %.0f, %.0f}", it->aabb.x, it->aabb.y, it->aabb.width, it->aabb.height);
    } else {
        TraceLog(LOG_ERROR, "Trying to add a new unit when array its full.");
    }
    
    return did_find_slot;
}

void UnitList::UpdateSelection(const Selector& selector) {
    if (!selector.IsSelecting()) {
        return;
    }

    auto is_active_unit = [](const auto& u) { return u.is_active; };
    for (auto& unit : units_ | std::views::filter(is_active_unit)) {
        const auto& a = unit.aabb;
        const auto& b = selector.GetArea();
        unit.is_selected = CheckCollisionRecs(a, b);
    }
}

const UnitList::Units& UnitList::GetUnits() const {
    return units_;
}

UnitList::Units& UnitList::GetUnits() {
    return units_;
}
