#pragma once

class ISelectable {
public:
    virtual ~ISelectable() = default;
    virtual void OnSelect() = 0;
    virtual void OnDeselect() = 0;
    virtual bool IsSelected() const = 0;
};
