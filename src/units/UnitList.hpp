#pragma once

#include "units/Unit.hpp"

#include "Selector.hpp"
#include "Config.hpp"

#include <array>

class UnitList {
public:
    using Units = std::array<Unit, kMaxTotalUnits>;

    UnitList();
    bool AddUnit(Rectangle aabb);
    void UpdateSelection(const Selector& selector);

    const Units& GetUnits() const;
    Units& GetUnits();

private:
    Units units_;
};
