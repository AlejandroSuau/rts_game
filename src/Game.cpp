#include "Game.hpp"
#include "Config.hpp"

namespace {
static const float kEntityWidth = 20;
static const float kEntityHeight = 20;
}

Game::Game(u32 width, u32 height, std::string_view title) 
    : width_(width), height_(height), title_(title) {}

void Game::Init() {
    selector_.Deselect();
    std::memset((void*)&units_, 0, sizeof(units_));
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

static void UpdateSelection(Units& units, const Selector& selector)
{
    if (!selector.IsSelecting()) {
        return;
    }
    for(u32 i = 0; i < kMaxTotalUnits; ++i) {
        if(!units.active[i]) {
            continue;
        }

        if (CheckCollisionRecs(units.aabb[i], selector.GetArea())) {
            units.selected[i] = true;
        } else {
            units.selected[i] = false;
        }
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

    UpdateSelection(units_, selector_);
}

void Game::SpawnEntity(const Vector2& coords) {
    for(u32 i = 0; i < kMaxTotalUnits; ++i) {
        if(units_.active[i]) {
            continue;
        }

        units_.active[i] = true;
        units_.selected[i] = false;
        units_.aabb[i] = {coords.x, coords.y, kEntityWidth, kEntityHeight};
        return;
    }
}

void Game::Draw() {
    BeginDrawing();
    
    ClearBackground(RAYWHITE);
    DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
    
    /* Draw basic unit */
    for(u32 i = 0; i < kMaxTotalUnits; ++i) {
        if(!units_.active[i]) {
            continue;
        }
    
        DrawRectangleLinesEx(units_.aabb[i], 1.0f, RED);
    }

    /* Draw unit selection decoration */
    for(u32 i = 0; i < kMaxTotalUnits; ++i) {
        if(!units_.active[i]) {
            continue;
        }
        if(!units_.selected[i]) {
            continue;
        }
        DrawRectangleLinesEx(units_.aabb[i], 2.0f, GREEN);
    }

    /* Draw selection */
    if (selector_.IsSelecting()) {
        const auto& area = selector_.GetArea();
        DrawRectangleLinesEx(area, 1.0f, BLUE);
    }
    
    EndDrawing();
}
