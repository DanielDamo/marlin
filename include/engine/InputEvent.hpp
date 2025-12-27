#pragma once
#include <string>

struct InputEvent {
    std::optional<std::string> action;   // hotkeys
    std::optional<std::string> command;  // typed stuff
};

