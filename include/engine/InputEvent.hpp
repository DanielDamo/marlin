#pragma once
#include <string>

enum class InputType {
    None,
    Character,
    Enter,
    Backspace,
    Escape,
    Up,
    Down
};

struct InputEvent {
    bool hasCommand = false;
    std::string command;
};