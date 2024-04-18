#include "TerminalTwaeks.hpp"

enum Arrows
{
    UP = 11,
    DOWN,
    RIGHT,
    LEFT
};

namespace TerminalTweaks 
{
    namespace Colors
    {
        std::string BLACK = "\033[30m";
        std::string RED = "\033[31m";
        std::string GREEN = "\033[32m";
        std::string YELLOW = "\033[33m";
        std::string BLUE = "\033[34m";
        std::string MAGENTA = "\033[35m";
        std::string CYAN = "\033[36m";
        std::string WHITE = "\033[37m";
        std::string BRIGHT_BLACK = "\033[90m";
        std::string BRIGHT_RED = "\033[91m";
        std::string BRIGHT_GREEN = "\033[92m";
        std::string BRIGHT_YELLOW = "\033[93m";
        std::string BRIGHT_BLUE = "\033[94m";
        std::string BRIGHT_MAGENTA = "\033[95m";
        std::string BRIGHT_CYAN = "\033[96m";
        std::string BRIGHT_WHITE = "\033[97m";
        
        std::string RESET = "\033[0m";
    }

    namespace BGColors
    {
        std::string BLACK = "\033[40m";
        std::string RED = "\033[41m";
        std::string GREEN = "\033[42m";
        std::string YELLOW = "\033[43m";
        std::string BLUE = "\033[44m";
        std::string MAGENTA = "\033[45m";
        std::string CYAN = "\033[46m";
        std::string WHITE = "\033[47m";
        std::string BRIGHT_BLACK = "\033[100m";
        std::string BRIGHT_RED = "\033[101m";
        std::string BRIGHT_GREEN = "\033[102m";
        std::string BRIGHT_YELLOW = "\033[103m";
        std::string BRIGHT_BLUE = "\033[104m";
        std::string BRIGHT_MAGENTA = "\033[105m";
        std::string BRIGHT_CYAN = "\033[106m";
        std::string BRIGHT_WHITE = "\033[107m";
        
        std::string RESET = "\033[0m";
    }

    namespace Styles
    {
        std::string BOLD = "\033[1m";
        std::string FAINT = "\033[2m";
        std::string ITALIC = "\033[3m";
        std::string UNDERLINE = "\033[4m";
        std::string SLOW_BLINK = "\033[5m";
        std::string RAPID_BLINK = "\033[6m";
        std::string REVERSED = "\033[7m";
        std::string CONCEAL = "\033[8m";
        std::string CROSSED_OUT = "\033[9m";
        std::string PRIMARY = "\033[10m";

        std::string RESET = "\033[0m";
    }

    void hideCursor()
    {
        std::cout << "\033[?25l";
    }

    void showCursor()
    {
        std::cout << "\033[?25h";
    }

    termios enableCbreak()
    {
        termios t, original;
        tcgetattr(STDIN_FILENO, &original);
        t = original;
        t.c_lflag &= ~ISIG;
        t.c_lflag &= ~ICANON;
        t.c_lflag &= ~ECHO;
        tcsetattr(STDIN_FILENO, TCSANOW, &t);
        return original;
    }

    void restoreTerminal(termios &t)
    {
        tcsetattr(STDIN_FILENO, TCSANOW, &t);
    }

    void getCursorPosition(int &row, int &col)
    {
        termios term;
        tcgetattr(STDOUT_FILENO, &term);

        std::cout << "\033[6n";
        std::string response;
        char ch;
        while (std::cin.get(ch) && ch != 'R')
        {
            response += ch;
        }
        sscanf(response.c_str(), "\033[%d;%dR", &row, &col);
    }

    void setCursorPosition(int row, int col)
    {
        std::cout << "\033[" << row << ";" << col << "H";
    }

    void clearScreen()
    {
        std::cout << "\033[2J\033[1;1H";
    }

    void clearScreenFromRow(int row)
    {
        std::cout << "\033[" << row << ";0H\033[J";
    }

    void clearLine()
    {
        std::cout << "\033[K";
    }

    char getInput()
    {
        char ch = getchar();
        if(ch == '\033')
        {
            ch = getchar();
            if(ch == '[')
            {
                switch (getchar())
                {
                case 'A':
                    return Arrows::UP;
                case 'B':
                    return Arrows::DOWN;
                case 'C':
                    return Arrows::RIGHT;
                case 'D':
                    return Arrows::LEFT;
                }
            }
        }
        return ch;
    }

    char getInputWithTimeout(int sec, int m_sec)
    {
        fd_set fds;
        FD_ZERO(&fds);
        FD_SET(STDIN_FILENO, &fds);
        timeval tv;
        tv.tv_sec = sec;
        tv.tv_usec = m_sec * 1000;
        int ret = select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);
        if(!(ret > 0 && FD_ISSET(STDIN_FILENO, &fds)))
        {
            return '\0';
        }
        return getInput();
    }

    size_t getSelectionFromMenu(std::vector<std::string> &options)
    {
        size_t selected = 0;
        auto terminal = enableCbreak();
        hideCursor();

        const char* arrow = " -> ";
        int startCursorRow, startCursorCol, endCursorRow, endCursorCol;
        getCursorPosition(startCursorRow, startCursorCol);

        bool waitingForSelection = true;

        while(waitingForSelection)
        {
            clearScreenFromRow(startCursorRow);

            for(size_t i = 0; i < options.size(); i++)
            {
                if(i == selected)
                {
                    std::cout <<
                        Styles::REVERSED <<
                        Styles::SLOW_BLINK <<
                        arrow <<
                        Styles::RESET <<
                        Styles::REVERSED <<
                        options[i] <<
                        Styles::RESET <<
                        std::endl;
                } 
                else 
                {
                    std::cout << " -  " << options[i] << std::endl;
                }
            }
            
            getCursorPosition(endCursorRow, endCursorCol);
            startCursorRow = endCursorRow - options.size();

            char ch = getInput();
            switch (ch)
            {
            case Arrows::UP:
                selected = (selected - 1 + options.size()) % options.size();
                break;
            case Arrows::DOWN:
                selected = (selected + 1) % options.size();
                break;
            case 'q':
            case 'Q':
            case '\033':
                selected = ~0;
            case '\n':
                waitingForSelection = false;
            }
        }
        clearScreenFromRow(startCursorRow);

        if(selected == (size_t)~0)
        {
            std::cout << Styles::FAINT << "Operation cancelled" << Styles::RESET << std::endl;
        } 
        else 
        {
            for (size_t i = 0; i < options.size(); i++)
            {
                if (i == selected)
                {
                    std::cout << Styles::BOLD << Colors::CYAN << arrow << options[i] << Styles::RESET << std::endl;
                }
                else 
                {
                    std::cout << " -  " << options[i] << std::endl;
                }
            }
            
        }

        showCursor();
        restoreTerminal(terminal);
        return selected;
    }
}

