#include "engine/SceneManager.hpp"
#include "engine/SaveSystem.hpp"

SceneManager::SceneManager(std::unique_ptr<Scene> startScene)
    : currentScene_(std::move(startScene)) {}

void SceneManager::handleInput(const InputEvent& input, GameState& gameState) {
    if (!currentScene_) return;

    // Typed commands
    if (input.command) {
        if (handleGlobalCommand(*input.command, gameState)) return;
        currentScene_->handleCommand(*input.command, gameState);
    }

    // Hotkey actions
    if (input.action) {
        currentScene_->handleAction(*input.action, gameState);
    }
}

void SceneManager::update(GameState& gameState, float dt) {
    if (!currentScene_) return;

    currentScene_->update(gameState, dt);

    if (auto next = currentScene_->takeNextScene()) {
        currentScene_->onExit(gameState);
        currentScene_ = std::move(next);
        currentScene_->onEnter(gameState);
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

SceneDrawData SceneManager::getDrawData() const {
    if (!currentScene_) {
        return {};
    }

    return currentScene_->getDrawData();
}

void SceneManager::transitionIfNeeded(GameState& gameState) {
    if (!currentScene_) return;

    auto next = currentScene_->takeNextScene();
    if (!next) return;

    // --- EXIT old scene ---
    currentScene_->onExit(gameState);

    // --- SWITCH scene ---
    currentScene_ = std::move(next);

    // --- ENTER new scene ---
    if (currentScene_) {
        currentScene_->onEnter(gameState);
    }
}

