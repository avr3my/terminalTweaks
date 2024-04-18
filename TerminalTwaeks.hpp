#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <termios.h>
#include <unistd.h>
#include <sys/select.h>

namespace TerminalTweaks 
{
    namespace Colors
    {
        extern std::string BLACK;
        extern std::string RED;
        extern std::string GREEN;
        extern std::string YELLOW;
        extern std::string BLUE;
        extern std::string MAGENTA;
        extern std::string CYAN;
        extern std::string WHITE;
        extern std::string BRIGHT_BLACK;
        extern std::string BRIGHT_RED;
        extern std::string BRIGHT_GREEN;
        extern std::string BRIGHT_YELLOW;
        extern std::string BRIGHT_BLUE;
        extern std::string BRIGHT_MAGENTA;
        extern std::string BRIGHT_CYAN;
        extern std::string BRIGHT_WHITE;

        extern std::string RESET;
    }

    namespace BGColors
    {
        extern std::string BLACK;
        extern std::string RED;
        extern std::string GREEN;
        extern std::string YELLOW;
        extern std::string BLUE;
        extern std::string MAGENTA;
        extern std::string CYAN;
        extern std::string WHITE;
        extern std::string BRIGHT_BLACK;
        extern std::string BRIGHT_RED;
        extern std::string BRIGHT_GREEN;
        extern std::string BRIGHT_YELLOW;
        extern std::string BRIGHT_BLUE;
        extern std::string BRIGHT_MAGENTA;
        extern std::string BRIGHT_CYAN;
        extern std::string BRIGHT_WHITE;

        extern std::string RESET;
    }

    namespace Styles
    {
        extern std::string BOLD;
        extern std::string FAINT;
        extern std::string ITALIC;
        extern std::string UNDERLINE;
        extern std::string SLOW_BLINK;
        extern std::string RAPID_BLINK;
        extern std::string REVERSED;
        extern std::string CONCEAL;
        extern std::string CROSSED_OUT;
        extern std::string PRIMARY;

        extern std::string RESET;
    }

    void hideCursor();
    void showCursor();
    termios enableCbreak();
    void restoreTerminal(termios &t);
    void getCursorPosition(int &row, int &col);
    void setCursorPosition(int row, int col);
    void clearScreen();
    void clearScreenFromRow(int row);
    void clearLine();
    char getInput();
    char getInputWithTimeout(int sec, int m_sec);
    size_t getSelectionFromMenu(std::vector<std::string> &options);
}

