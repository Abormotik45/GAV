#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <cstdlib>


int hunt() {
    std::vector<std::vector<std::string>> frames = {
        {
            "  /\\_/\\          >~:3  ",
            " ( o.o )   __/        ",
            "  =^_^=─\\             ",
            " /     \\ \\            ",
            "|       |             ",
            "~~~~~~~~~~~~~~~~~~~~~~"
        },
        {
            "    /\\_/\\        >~:3 ",
            "   ( O-O ) _/        ",
            "    =^_^=─\\          ",
            "   /     \\ \\         ",
            "  |       |          ",
            "~~~~~~~~~~~~~~~~~~~~~~"
        },
        {
            "      /\\_/\\      >~:3",
            "     ( >< ) /        ",
            "      =^_^=─\\        ",
            "     /     \\ \\       ",
            "    |       |        ",
            "~~~~~~~~~~~~~~~~~~~~~~"
        },
        {
            "        /\\_/\\≧◉ᴥ◉≦   ",
            "       ( X_X )       ",
            "        =^_^=        ",
            "       /     \\       ",
            "      |       |      ",
            "~~~~~~~~~~~~~~~~~~~~~~"
        }
    };

    for(const auto& frame : frames) {
        clearScreen();
        for(const auto& line : frame) {
            std::cout << line << '\n';
        }
        std::cout << std::flush;
        
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    return 0;
}