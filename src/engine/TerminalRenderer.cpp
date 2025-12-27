#include "engine/TerminalRenderer.hpp"
#include <ncurses.h>
#include <variant>
#include <string>
#include <algorithm>
#include <cctype>
#include <string>

TerminalRenderer::~TerminalRenderer() {}

TerminalRenderer::TerminalRenderer() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    nodelay(stdscr, TRUE);

    int h, w;
    getmaxyx(stdscr, h, w);

    int usableHeight = h - INPUT_HEIGHT;

    int mainWidth  = w;
    int mainHeight = static_cast<int>(mainWidth / MAIN_ASPECT);

    if (mainHeight > usableHeight) {
        mainHeight = usableHeight;
        mainWidth  = static_cast<int>(mainHeight * MAIN_ASPECT);
    }

    int mainX  = (w - mainWidth) / 2;
    int mainY  = (usableHeight - mainHeight) / 2;
    int inputY = h - INPUT_HEIGHT;

    frameWin = newwin(h, w, 0, 0);
    mainWin  = newwin(mainHeight, mainWidth, mainY, mainX);
    inputWin = newwin(INPUT_HEIGHT, w, inputY, 0);
    popupWin = newwin(7, w / 2, h / 2 - 3, w / 4);
}


void TerminalRenderer::render(const SceneDrawData& data) {
    rebuildHotkeys(data);

    // Clear windows
    werase(frameWin);
    werase(mainWin);
    werase(inputWin);

    box(mainWin, 0, 0);
    box(inputWin, 0, 0);

    int line = 1;

    for (const auto& widget : data.widgets) {
        std::visit([&](auto&& w) {
            using T = std::decay_t<decltype(w)>;

            if constexpr (std::is_same_v<T, TextBlock>) {
                printWrapped(mainWin, line, 2, w.text);
            }

            else if constexpr (std::is_same_v<T, Menu>) {
                mvwprintw(mainWin, line++, 2, "%s", w.title.c_str());
                for (const auto& opt : w.options) {
                    mvwprintw(mainWin, line++, 4,
                        "[%c] %s", opt.hotkey, opt.label.c_str());
                }
            }

            else if constexpr (std::is_same_v<T, ProgressBar>) {
                int barW = 20;
                int fill = static_cast<int>(
                    (w.progress / w.maxProgress) * barW
                );
                std::string bar(fill, '=');
                bar += std::string(barW - fill, ' ');
                mvwprintw(mainWin, line++, 2,
                    "%s [%s]", w.label.c_str(), bar.c_str());
            }

            else if constexpr (std::is_same_v<T, ResourceMeter>) {
                mvwprintw(mainWin, line++, 2,
                    "%s: %d/%d", w.label.c_str(), w.current, w.max);
            }
        }, widget.data);
    }

    mvwprintw(inputWin, 1, 2, "> %s", inputBuffer.c_str());


    wnoutrefresh(frameWin);
    wnoutrefresh(mainWin);
    wnoutrefresh(inputWin);
    doupdate();
}


static std::string trim(const std::string& s) {
    size_t start = 0;
    while (start < s.size() && std::isspace(static_cast<unsigned char>(s[start]))) start++;

    size_t end = s.size();
    while (end > start && std::isspace(static_cast<unsigned char>(s[end - 1]))) end--;

    return s.substr(start, end - start);
}

InputEvent TerminalRenderer::pollInput() {
    int ch = getch();
    if (ch == ERR) return {};

    // HOTKEY: instant command
    if (hotkeyMap.count(ch)) {
        return InputEvent{ hotkeyMap[ch], std::nullopt };
    }

    // ENTER: typed command
    if (ch == '\n') {
        if (!inputBuffer.empty()) {
            std::string command = trim(inputBuffer);
            inputBuffer.clear();
            if (!command.empty()) {
                return InputEvent{ std::nullopt, command };
            }
        }
        return {};
    }

    // BACKSPACE
    if (ch == KEY_BACKSPACE || ch == 127) {
        if (!inputBuffer.empty()) inputBuffer.pop_back();
        return {};
    }

    // TEXT INPUT
    if (ch >= 32 && ch <= 126) {
        inputBuffer.push_back(static_cast<char>(ch));
    }

    return {};
}



void TerminalRenderer::printWrapped(
        WINDOW* win,
        int& line,
        int x,
        const std::string& text
    ) {
    int h, w;
    getmaxyx(win, h, w);
    int maxWidth = w - x - 2; // keep off the border

    size_t start = 0;
    while (start < text.size()) {
        std::string chunk = text.substr(start, maxWidth);
        mvwprintw(win, line++, x, "%s", chunk.c_str());
        start += maxWidth;

        if (line >= h - 1) break; // don’t smash bottom border
    }
}



void TerminalRenderer::rebuildHotkeys(const SceneDrawData& data) {
    hotkeyMap.clear();

    for (const auto& widget : data.widgets) {
        std::visit([&](auto&& w) {
            using T = std::decay_t<decltype(w)>;

            if constexpr (std::is_same_v<T, Menu>) {
                for (const auto& opt : w.options) {
                    hotkeyMap[opt.hotkey] = opt.command;
                }
            }
        }, widget.data);
    }
}

