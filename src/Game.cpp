#include "Game.hpp"
#include "Config.hpp"

#include <slib/profiler.h>

namespace {
    static const float kEntityWidth = 20;
    static const float kEntityHeight = 20;
}

Game::Game(u32 width, u32 height, std::string_view title) 
    : width_(width), height_(height), title_(title), units_{} {}

    void Game::Init() {
        DisableCursor();

        selector_.Deselect();
        cursor_.x = kWindowWidth / 2.f;
        cursor_.y = kWindowHeight / 2.f;
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

Vector2 UpdateCursor(const Vector2& old, const Vector2& delta)
{
    Vector2 next;
    next.x = old.x + delta.x;
    next.y = old.y + delta.y;

    next.x = std::max(0.f, next.x);
    next.x = std::min((f32)kWindowWidth, next.x);
    next.y = std::max(0.f, next.y);
    next.y = std::min((f32)kWindowWidth, next.y);

    return next;
}

void Game::Update() {
    PROFILE_FUNCTION;

    Vector2 mouseDelta = GetMouseDelta();
    cursor_ = UpdateCursor(cursor_, mouseDelta);


    if (IsKeyPressed(KEY_A)) {
        SpawnEntity(cursor_);
    }

    selector_.HandleSelection(
            cursor_,
            IsMouseButtonDown(MOUSE_BUTTON_LEFT),
            IsMouseButtonReleased(MOUSE_BUTTON_LEFT));

    units_.UpdateSelection(selector_);
}

void Game::SpawnEntity(const Vector2& coords) {
    PROFILE_FUNCTION;
    units_.AddUnit({coords.x, coords.y, kEntityWidth, kEntityHeight});
}

void Game::Draw() {
    PROFILE_FUNCTION;
    BeginDrawing();

    ClearBackground(RAYWHITE);
    DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

    // TODO: Maybe Unit itself controls its drawing (even selected draw too).
    /* Draw basic unit */
    {
        PROFILE_BLOCK("Draw Units");

        for(const auto& unit : units_.GetUnits())
        {
            if(!unit.is_active)
                continue;

            DrawRectangleLinesEx(unit.aabb, 1.0f, RED);

            if (unit.is_selected) {
                DrawRectangleLinesEx(unit.aabb, 2.0f, GREEN);
            }
        }
    }

    /* Draw selection */
    if (selector_.IsSelecting()) {
        const auto& area = selector_.GetArea();
        DrawRectangleLinesEx(area, 1.0f, BLUE);
    }

    DrawRectangleLines((i32)cursor_.x, (i32)cursor_.y, 10, 10, BLACK);

    EndDrawing();
}
