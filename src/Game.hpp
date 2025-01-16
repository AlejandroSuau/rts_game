#pragma once

#include "Selector.hpp"
#include "Entity.hpp"

#include <string>
#include <vector>
#include <memory>

class Game {
public:
    Game(int width, int height, std::string title);
    void Run();

private:
    int width_;
    int height_;
    const std::string title_;

    std::vector<std::unique_ptr<Entity>> entities_;
    
    Selector selector_;

    void Init();
    void Update();
    void Draw();
};
