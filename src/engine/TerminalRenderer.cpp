#include "engine/TerminalRenderer.hpp"

TerminalRenderer::~TerminalRenderer() {}

TerminalRenderer::TerminalRenderer(float proportion) {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    nodelay(stdscr, TRUE);

    int termHeight, termWidth;
    getmaxyx(stdscr, termHeight, termWidth);

    int mainHeight = termHeight * proportion;
    int inputHeight = termHeight - mainHeight;

    mainWin = newwin(mainHeight, termWidth, 0, 0);
    inputWin = newwin(inputHeight, termWidth, mainHeight, 0);
}

void TerminalRenderer::render(const SceneDrawData& data) {
    // Clear windows
    werase(mainWin);
    werase(inputWin);

    // Draw borders
    box(mainWin, 0, 0);
    box(inputWin, 0, 0);

    // --- Main window content ---
    mvwprintw(mainWin, 1, 2, "%s", data.topText.c_str());

    for (size_t i = 0; i < data.menuOptions.size(); i++) {
        mvwprintw(mainWin, 3 + i, 4, "%s", data.menuOptions[i].c_str());
    }

    // --- Input window content ---
    // Print input prompt
    mvwprintw(inputWin, 1, 2, "%s", data.inputPrompt.c_str());

    // Compute start X for input buffer (after prompt)
    int inputStartX = 2 + data.inputPrompt.size();

    // Print current input buffer
    mvwprintw(inputWin, 1, inputStartX, "%s", inputBuffer.c_str());
    
    // Refresh windows to show changes
    wrefresh(mainWin);
    wrefresh(inputWin);
}



InputEvent TerminalRenderer::pollInput() {
    int ch = getch();

    if (ch == ERR) {
        return {};
    }

    if (ch == '\n') {
        InputEvent event{ true, inputBuffer };
        inputBuffer.clear();
        return event;
    }

    if (ch == KEY_BACKSPACE || ch == 127) {
        if (!inputBuffer.empty()) {
            inputBuffer.pop_back();
        }
        return {};
    }

    if (ch >= 32 && ch <= 126) {
        inputBuffer.push_back(static_cast<char>(ch));
    }

    return {};
}

