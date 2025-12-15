#pragma once
#include "engine/Renderer.hpp"
#include <ncurses.h>

class TerminalRenderer : public Renderer {
    WINDOW* mainWin;
    WINDOW* inputWin;

    float topScreenProportion;

    std::string inputBuffer;
    int cursorX = 2;

    public:
        TerminalRenderer(float proportion);
        ~TerminalRenderer();

        void render(const SceneDrawData& data) override;
        InputEvent pollInput() override;
};