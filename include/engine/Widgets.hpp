#pragma once
#include <string>
#include <vector>
#include <variant>
#include <optional>

//
// ---- Widget data types ----
//

// Text block (titles, messages)
struct TextBlock {
    std::string text;
    // TextStyle style; // optional in future
};

// Progress bar (reloads, travel, cooldowns)
struct ProgressBar {
    std::string label;
    float progress;        // 0.0 -> 1.0
    float maxProgress = 1.0f;
    std::optional<char> hotkey;  // e.g. '4' to fire
};

// Resource meter / ammo counter
struct ResourceMeter {
    std::string label;
    int current;
    int max;
    std::optional<char> hotkey;
};

// Menu system
struct MenuOption {
    char hotkey;
    std::string label;
    std::string command;  
};


struct Menu {
    std::string title;
    std::vector<MenuOption> options;
};

// Status list (optional, for ship stats etc.)
struct StatusItem {
    std::string label;
    std::string value;
};

struct StatusList {
    std::vector<StatusItem> items;
};

//
// ---- Unified widget type ----
//
using WidgetData = std::variant<
    TextBlock,
    ProgressBar,
    ResourceMeter,
    Menu,
    StatusList
>;

struct WidgetMeta {
    std::string group;
    int order;
};

struct Widget {
    WidgetMeta meta;
    WidgetData data;
};
