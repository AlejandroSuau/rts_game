#include "Game.hpp"
#include <cmath>

namespace {
static const int kTargetFPS = 60;

static const float kEntityWidth = 20;
static const float kEntityHeight = 20;
}

Game::Game(int width, int height, std::string title) 
    : width_(width), height_(height), title_(title) {}

void Game::Run() {
    InitWindow(width_, height_, title_.c_str());
    SetTargetFPS(kTargetFPS);

    while (!WindowShouldClose()) {
        this->Update();
        this->Draw();
    }
}

void Game::Update() {
    RTSCoords mouse = GetMousePosition();

    if (IsKeyPressed(KEY_A)) {
        entities_.emplace_back(
            std::make_unique<Entity>(RTSRect{mouse.x, mouse.y, kEntityWidth, kEntityHeight}));
    }


    selector_.HandleSelection(
        mouse,
        IsMouseButtonDown(MOUSE_BUTTON_LEFT),
        IsMouseButtonReleased(MOUSE_BUTTON_LEFT));
}

void Game::Draw() {
    BeginDrawing();
    
    ClearBackground(RAYWHITE);
    DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
        
    for (const auto& e : entities_) {
        e->Draw();
    }

    // Draw Selector
    if (selector_.IsSelecting()) {
        const auto& selecting_area_ = selector_.GetArea();
        DrawRectangleLines(
            (int)selecting_area_.x,
            (int)selecting_area_.y,
            (int)selecting_area_.width,
            (int)selecting_area_.height,
            BLUE);
    }
    
    EndDrawing();
}
