#include "Config.hpp"
#include "Game.hpp"
#include <slib/profiler.h>

int main() {
    profiling_begin();

    Game game(kWindowWidth, kWindowHeight, kWindowTitle);
    game.Run();

    profiling_end();
}
