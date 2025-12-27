#pragma once
#include "engine/Renderer.hpp"
#include <ncurses.h>
#include <unordered_map>


class TerminalRenderer : public Renderer {
    WINDOW* frameWin  = nullptr;
    WINDOW* mainWin   = nullptr;
    WINDOW* inputWin  = nullptr;
    WINDOW* popupWin  = nullptr;

    std::string inputBuffer;
    int cursorX = 2;

    std::unordered_map<char, std::string> hotkeyMap;

    public:
        TerminalRenderer();
        ~TerminalRenderer();

        void render(const SceneDrawData& data) override;
        InputEvent pollInput() override;
    
    private:
        static constexpr float ACROSS_RATIO = 19.0f;
        static constexpr float UP_RATIO = 10.0f;
        static constexpr int CHARACTER_WIDTH_PARAM = 2;
        static constexpr float MAIN_ASPECT = (ACROSS_RATIO * CHARACTER_WIDTH_PARAM) / UP_RATIO;
        static constexpr int INPUT_HEIGHT = 3;

        void rebuildHotkeys(const SceneDrawData& data);
        void printWrapped(WINDOW* win, int& line, int x, const std::string& text);
};

