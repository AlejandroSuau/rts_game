#include "Game.hpp"
#include "Config.hpp"

#include <ranges>

namespace {
static const float kEntityWidth = 20;
static const float kEntityHeight = 20;
}

Game::Game(u32 width, u32 height, std::string_view title) 
    : width_(width), height_(height), title_(title), units_{} {}

void Game::Init() {
    selector_.Deselect();
}

void Game::Run() {
    InitWindow(width_, height_, title_.data());
    SetTargetFPS(kTargetFPS);

    Init();

    while (!WindowShouldClose()) {
        this->Update();
        this->Draw();
    }
}

void Game::Update() {
    Vector2 mouse = GetMousePosition();

    if (IsKeyPressed(KEY_A)) {
        SpawnEntity(mouse);
    }

    selector_.HandleSelection(
        mouse,
        IsMouseButtonDown(MOUSE_BUTTON_LEFT),
        IsMouseButtonReleased(MOUSE_BUTTON_LEFT));

    units_.UpdateSelection(selector_);
}

void Game::SpawnEntity(const Vector2& coords) {
    units_.AddUnit({coords.x, coords.y, kEntityWidth, kEntityHeight});
}

void Game::Draw() {
    BeginDrawing();
    
    ClearBackground(RAYWHITE);
    DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
    
    // TODO: Maybe Unit itself controls its drawing (even selected draw too).
    /* Draw basic unit */
    const auto& units = units_.GetUnits();
    auto is_active_unit = [](const auto& u) { return u.is_active; };
    for (const auto& unit : units | std::views::filter(is_active_unit)) {
        DrawRectangleLinesEx(unit.aabb, 1.0f, RED);
        
        /* Draw unit selection decoration */
        if (unit.is_selected) {
            DrawRectangleLinesEx(unit.aabb, 2.0f, GREEN);
        }
    }

    /* Draw selection */
    if (selector_.IsSelecting()) {
        const auto& area = selector_.GetArea();
        DrawRectangleLinesEx(area, 1.0f, BLUE);
    }
    
    EndDrawing();
}
