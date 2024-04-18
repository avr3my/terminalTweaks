#include <iostream>
#include "TerminalTwaeks.hpp"

int main(int argc, char **argv)
{
    std::cout << "Starting Progran" << std::endl;

    std::vector<std::string> options = {
        "Option A",
        "Option B",
        "Option C",
        "Option D",
        "Option E",
        "Option F",
    };

    size_t selected = TerminalTweaks::getSelectionFromMenu(options);
    std::cout << "Selected: " << selected << ". " <<options[selected] << std::endl;
    return 0;
}