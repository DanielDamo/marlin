#pragma once
#include <memory>
#include "engine/SceneDrawData.hpp"
#include "engine/GameState.hpp"

class GameState;

class Scene {
public:
    virtual ~Scene() = default;

    virtual void handleCommand(const std::string&, GameState&) {}
    virtual void update(GameState&) {}

    virtual SceneDrawData getDrawData() const = 0;

    // Scene requests transition by returning ownership
    virtual std::unique_ptr<Scene> takeNextScene() { return nullptr; }
};
