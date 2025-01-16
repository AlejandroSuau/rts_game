#include "Entity.hpp"

Entity::Entity(const RTSRect& rect)
    : rect_(rect) {}
        
void Entity::Draw() {
    DrawRectangleLinesEx(rect_, 1.f, RED);
}