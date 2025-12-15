#pragma once

#include <memory>
#include <string>

#include "engine/Scene.hpp"
#include "engine/GameState.hpp"
#include "engine/SceneDrawData.hpp"

class SceneManager {
public:
    explicit SceneManager(std::unique_ptr<Scene> startScene);
    ~SceneManager() = default;

    // Called when the renderer finishes a command (Enter pressed)
    void handleCommand(const std::string& command, GameState& gameState);

    // Called every frame (for animations, timers, etc.)
    void update(GameState& gameState);

    // Renderer pulls this to know what to draw
    SceneDrawData getDrawData() const;

private:
    void transitionIfNeeded();
    bool handleGlobalCommand(const std::string& command, GameState& gameState);

    std::unique_ptr<Scene> currentScene_;
};
