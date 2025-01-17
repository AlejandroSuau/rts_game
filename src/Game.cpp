#include "Game.hpp"

#include "components/selectable/SelectableComponent.hpp"

#include <iostream>

namespace {
static const int kTargetFPS = 60;

static const float kEntityWidth = 20;
static const float kEntityHeight = 20;
}

Game::Game(int width, int height, std::string title) 
    : width_(width), height_(height), title_(title) {}

void Game::Init() {
    selector_.Deselect();
}

void Game::Run() {
    InitWindow(width_, height_, title_.c_str());
    SetTargetFPS(kTargetFPS);

    Init();

    while (!WindowShouldClose()) {
        this->Update();
        this->Draw();
    }
}

void Game::Update() {
    RTSCoords mouse = GetMousePosition();

    if (IsKeyPressed(KEY_A)) {
        SpawnEntity(mouse);
    }

    selector_.HandleSelection(
        mouse,
        IsMouseButtonDown(MOUSE_BUTTON_LEFT),
        IsMouseButtonReleased(MOUSE_BUTTON_LEFT));
    
    // Selecting entities
    for (const auto& e : entities_) {
        auto selectable = e->GetComponent<SelectableComponent>();
        if (!selectable) continue;

        if (selector_.IsSelecting()) {
            if (CheckCollisionRecs(e->GetRect(), selector_.GetArea())) {
                selectable->OnSelect();
            } else {
                selectable->OnDeselect();
            }
        }
    }
}

void Game::SpawnEntity(RTSCoords coords) {
    // TODO: thought we can do auto& e = entities_.emplace_back(...);
    entities_.emplace_back(
        std::make_unique<Entity>(RTSRect{coords.x, coords.y, kEntityWidth, kEntityHeight}));
    entities_.back()->AddComponent(std::make_shared<SelectableComponent>());
}

void Game::Draw() {
    BeginDrawing();
    
    ClearBackground(RAYWHITE);
    DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
    
    for (const auto& e : entities_) {
        e->Draw();
    }

    /**
     * Draw selector
    */
    if (selector_.IsSelecting()) {
        const auto& selecting_area_ = selector_.GetArea();
        DrawRectangleLines(
            static_cast<int>(selecting_area_.x),
            static_cast<int>(selecting_area_.y),
            static_cast<int>(selecting_area_.width),
            static_cast<int>(selecting_area_.height),
            BLUE);
    }

    /**
     * Draw selected entities decorator
     */
    for (const auto& e : entities_) {
        auto selectable = e->GetComponent<SelectableComponent>();
        if (selectable && selectable->IsSelected()) {
            selectable->DrawSelectionIndicator(e->GetRect());
        }
    }
    
    EndDrawing();
}
