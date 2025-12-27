#pragma once

#include <memory>
#include <unordered_map>
#include <functional>
#include <string>

#include "engine/SceneDrawData.hpp"
#include "engine/GameState.hpp"
#include "engine/InputEvent.hpp"

class Scene;

// ---- Scene transition result ----
struct NextSceneStruct {
    bool changeScene = false;
    std::unique_ptr<Scene> nextScene;
};

class Scene {
public:
    virtual ~Scene() = default;

    // Lifecycle
    virtual void onEnter(GameState&) {}
    virtual void onExit(GameState&) {}

    // Per-frame update
    virtual void update(GameState&, float dt) {}

    // Input handling
    virtual void handleAction(const std::string&, GameState&);
    virtual void handleCommand(const std::string&, GameState&);

    // Rendering
    virtual SceneDrawData getDrawData() const = 0;

    // Transition query
    std::unique_ptr<Scene> takeNextScene();

protected:
    using SceneFactory = std::function<std::unique_ptr<Scene>()>;
    using ActionHandler = std::function<void(GameState&)>;

    std::unordered_map<std::string, SceneFactory> commandMap;
    std::unordered_map<std::string, ActionHandler> actionMap;

    std::unique_ptr<Scene> pendingScene;
};
