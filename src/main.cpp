#include "engine/TerminalRenderer.hpp"
#include "engine/Scene.hpp"
#include "engine/SceneDrawData.hpp"
#include "Ship.hpp"
#include "engine/SceneManager.hpp"


#include <ncurses.h>
#include <iostream>

//TEMP
class MenuScene : public Scene {
    public:
        SceneDrawData getDrawData() const override {
            SceneDrawData data;
            data.topText = "Ahoy!";
            data.art = "#'asd#'a#sd";
            data.menuOptions = {
                "1) Set Sail",
                "2) Fire Cannons",
                "3) Abandon Ship"
            };
            data.inputPrompt = "> ";

            return data;
        };
};

int main() {
    // --- Initialise renderer ---
    std::unique_ptr<Renderer> renderer = std::make_unique<TerminalRenderer>(0.9);

    // --- Initialise SceneManager and first scene ---
    SceneManager sceneManager(std::make_unique<MenuScene>());
    GameState gameState;

    // --- Main Loop ----
    bool running = true;
    while (running) {
        auto input = renderer->pollInput();

        if (input.hasCommand) {
            sceneManager.handleCommand(input.command, gameState);
        }

        sceneManager.update(gameState);
        renderer->render(sceneManager.getDrawData());
    }

    return 0;
}