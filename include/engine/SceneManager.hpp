#pragma once

#include <memory>
#include <string>

#include "engine/Scene.hpp"
#include "engine/GameState.hpp"
#include "engine/SceneDrawData.hpp"

class SceneManager {
public:
    explicit SceneManager(std::unique_ptr<Scene> startScene);
    // Handle Inputs
    void handleInput(const InputEvent& input, GameState& gamestate);
    // Per-frame update
    void update(GameState& gameState, float deltaTime);
    // Data for renderer
    SceneDrawData getDrawData() const;

private:
    std::unique_ptr<Scene> currentScene_;
    // Global commands like save/load
    bool handleGlobalCommand(const std::string& command, GameState& gameState);
    // Scene transitions
    void transitionIfNeeded(GameState& gameState);
};
