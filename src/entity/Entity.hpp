#pragma once

#include "Types.hpp"

#include <typeindex>
#include <unordered_map>
#include <memory>

class Entity {
public:
    using ComponentsMap = std::unordered_map<std::type_index, std::shared_ptr<void>>;

    Entity(const RTSRect& rect) 
        : rect_(rect) {}

    template <typename T>
    void AddComponent(std::shared_ptr<T> component) {
        components_[std::type_index(typeid(T))] = component;
    }

    // TODO: Can be std::shared_ptr<T>& instead?
    template <typename T>
    std::shared_ptr<T> GetComponent() {
        auto it = components_.find(std::type_index(typeid(T)));
        if (it != components_.end()) {
            return std::static_pointer_cast<T>(it->second);
        }
        return nullptr;
    }   

    void Draw() {
        DrawRectangleLinesEx(rect_, 1.f, RED);
    }

    const RTSRect& GetRect() const {
        return rect_;
    }

private:
    RTSRect rect_;
    ComponentsMap components_;
};