#pragma once
#include <nlohmann/json.hpp>
#include "engine/GameState.hpp"

using json = nlohmann::json;

constexpr int SAVE_VERSION = 1;

inline json serializeGameState(const GameState& s) {
    return {
        {"player", {
            {"name", s.player.name},
            {"gold", s.player.gold},
            {"health", s.player.health}
        }},
        {"ship", {
            {"name", s.ship.shipName},
            {"hull", s.ship.hull},
            {"cannons", s.ship.cannons},
            {"crew", s.ship.crew}
        }},
        {"world", {
            {"currentLocation", s.world.currentLocation},
            {"ports", s.world.discoveredPorts}
        }},
        {"flags", s.flags},
        {"rngSeed", s.rngSeed},
        {"playTime", s.playTimeSeconds}
    };
}

inline bool deserializeGameState(const json& j, GameState& s) {
    try {
        s.player.name   = j.at("player").at("name");
        s.player.gold   = j.at("player").at("gold");
        s.player.health = j.at("player").at("health");

        s.ship.shipName = j.at("ship").at("name");
        s.ship.hull     = j.at("ship").at("hull");
        s.ship.cannons  = j.at("ship").at("cannons");
        s.ship.crew     = j.at("ship").at("crew");

        s.world.currentLocation = j.at("world").at("currentLocation");
        s.world.discoveredPorts = j.at("world").at("ports");

        s.flags = j.at("flags").get<std::unordered_set<std::string>>();

        s.rngSeed = j.at("rngSeed");
        s.playTimeSeconds = j.at("playTime");
    }
    catch (...) {
        return false;
    }
    return true;
}
