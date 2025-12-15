#include "engine/SaveSystem.hpp"
#include "engine/serialisation/GameStateJson.hpp"

#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

std::string SaveSystem::saveDirectory() {
    return "saves";
}

std::string SaveSystem::savePathForSlot(const std::string& slot) {
    return saveDirectory() + "/" + slot + ".json";
}

void SaveSystem::save(const GameState& state, const std::string& slot) {
    fs::create_directories(saveDirectory());

    json root;
    root["version"] = SAVE_VERSION;
    root["state"] = serializeGameState(state);

    std::ofstream file(savePathForSlot(slot));
    file << root.dump(4);
}

LoadResult SaveSystem::load(GameState& state, const std::string& slot) {
    std::ifstream file(savePathForSlot(slot));
    if (!file.is_open()) {
        return LoadResult::NotFound;
    }

    json root;
    try {
        file >> root;
    }
    catch (...) {
        return LoadResult::Corrupt;
    }

    if (!root.contains("version") || root["version"] != SAVE_VERSION) {
        return LoadResult::VersionMismatch;
    }

    if (!root.contains("state")) {
        return LoadResult::Corrupt;
    }

    if (!deserializeGameState(root["state"], state)) {
        return LoadResult::Corrupt;
    }

    return LoadResult::Success;
}

std::vector<std::string> SaveSystem::listSaves() {
    std::vector<std::string> result;

    if (!fs::exists(saveDirectory())) {
        return result;
    }

    for (auto& entry : fs::directory_iterator(saveDirectory())) {
        if (entry.path().extension() == ".json") {
            result.push_back(entry.path().stem().string());
        }
    }

    return result;
}
