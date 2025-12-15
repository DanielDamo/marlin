#pragma once

#include <string>
#include <vector>
#include "engine/GameState.hpp"

enum class LoadResult {
    Success,
    NotFound,
    Corrupt,
    VersionMismatch
};

class SaveSystem {
public:
    static void save(const GameState& state,
                     const std::string& slot = "autosave");

    static LoadResult load(GameState& state,
                           const std::string& slot = "autosave");

    static std::vector<std::string> listSaves();

private:
    static std::string saveDirectory();
    static std::string savePathForSlot(const std::string& slot);
};
