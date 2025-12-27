#include "engine/TerminalRenderer.hpp"
#include "engine/Scene.hpp"
#include "engine/SceneDrawData.hpp"
#include "Ship.hpp"
#include "engine/SceneManager.hpp"
#include "scenes/MainMenu.hpp"


#include <ncurses.h>
#include <iostream>
#include <chrono>


int main() {
    // --- Initialise renderer ---
    std::unique_ptr<Renderer> renderer = std::make_unique<TerminalRenderer>();

    // --- Initialise SceneManager and first scene ---
    SceneManager sceneManager(std::make_unique<MainMenu>());
    GameState gameState;

    // --- Initialise time stuff ---
    auto lastTime = std::chrono::high_resolution_clock::now();

    // --- Main Loop ----
    bool running = true;
    while (running) {
        auto now = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> elapsed = now - lastTime;
        lastTime = now;
        float deltaTime = elapsed.count();

        auto input = renderer->pollInput();

        
        sceneManager.handleInput(input, gameState);
        sceneManager.update(gameState, deltaTime);
        renderer->render(sceneManager.getDrawData());
        
    }

    return 0;
}