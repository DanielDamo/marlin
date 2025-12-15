#include "engine/SceneManager.hpp"
#include "engine/SaveSystem.hpp"

SceneManager::SceneManager(std::unique_ptr<Scene> startScene)
    : currentScene_(std::move(startScene)) {}

void SceneManager::handleCommand(const std::string& command, GameState& gameState) {
    // Global commands, saves etc
    if (handleGlobalCommand(command, gameState)) {
        return;
    }

    if (currentScene_) {
        currentScene_->handleCommand(command, gameState);
        transitionIfNeeded();
    }
}

bool SceneManager::handleGlobalCommand(const std::string& command,
                                       GameState& gameState) {
    if (command == "save") {
        SaveSystem::save(gameState);
        return true;
    }

    if (command == "load") {
        SaveSystem::load(gameState);
        return true;
    }

    if (command == "listsaves") {
        SaveSystem::listSaves();
        return true;
    }

    return false;
}

void SceneManager::update(GameState& gameState) {
    if (!currentScene_) return;

    currentScene_->update(gameState);
    transitionIfNeeded();
}

SceneDrawData SceneManager::getDrawData() const {
    if (!currentScene_) {
        return {};
    }
    return currentScene_->getDrawData();
}

void SceneManager::transitionIfNeeded() {
    if (auto next = currentScene_->takeNextScene()) {
        currentScene_ = std::move(next);
    }
}
