#pragma once

#include <string>
#include <vector>
#include <unordered_set>
#include <cstdint>

struct PlayerState {
    std::string name;
    int gold = 0;
    int health = 100;
};

struct ShipState {
    std::string shipName;
    int hull = 100;
    int cannons = 4;
    int crew = 10;
};

struct WorldState {
    std::string currentLocation;
    std::vector<std::string> discoveredPorts;
};

struct GameState {
    PlayerState player;
    ShipState ship;
    WorldState world;

    std::unordered_set<std::string> flags;

    uint32_t rngSeed = 0;
    uint64_t playTimeSeconds = 0;
};
