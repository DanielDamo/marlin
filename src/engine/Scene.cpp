#include "engine/Scene.hpp"

void Scene::handleCommand(const std::string& command, GameState&) {
    auto it = commandMap.find(command);
    if (it == commandMap.end()) return;

    pendingScene = it->second();
}


void Scene::handleAction(const std::string& action, GameState& gameState) {
    auto it = actionMap.find(action);
    if (it == actionMap.end()) return;

    it->second(gameState);
}


std::unique_ptr<Scene> Scene::takeNextScene() {
    return std::move(pendingScene);
}
