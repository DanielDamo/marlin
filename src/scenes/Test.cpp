#include "scenes/Test.hpp"
#include "scenes/MainMenu.hpp"

Test::Test() {
    commandMap = {
        { "start", [] { return std::make_unique<MainMenu>(); } },
        { "quit", [] { return nullptr; } }
    };

    actionMap = {
        { "scroll_up",   [this](GameState& g) { /*scrollUp(g); */} },
        { "scroll_down", [](GameState&) { /* move cursor */ } },
        { "select",      [](GameState&) { /* confirm choice */ } }
    };
}

void Test::onEnter(GameState& gameState) {

}
void Test::onExit(GameState& gameState) {
    
}
void Test::update(GameState& gameState, float dt) {
    
}

SceneDrawData Test::getDrawData() const {
    SceneDrawData data;

    data.widgets.push_back(Widget{
        TextBlock{ "Ahoy, Captain 2!" }
    });

    data.widgets.push_back(Widget{
        Menu{
            "Main Menu",
            {
                { '1', "Set Sail",     "scroll_up" },
                { '2', "Fire Cannons", "practice_fire" },
                { '3', "Abandon Ship", "abandon_ship" }
            }
        }
    });

    data.widgets.push_back(Widget{
        TextBlock{ "Type 'quit' and press Enter to leave the game." }
    });

    return data;
}
