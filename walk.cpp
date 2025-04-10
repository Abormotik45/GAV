#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <string>

using namespace std;

int walk() {
    // Default FPS if not provided
    int fps = 4;

    // Animation frames stored in vector
    vector<vector<string>> frames = {
        {  // Frame 1 - Mid stride
            "   /\\_/\\    ",
            "  ( o ◡ o )  ",
            "  _\\  /\\_  ",
            "  /_/  \\ \\ ",
            "  |_|  |_|   ",
            "  / \\  / \\  "
        },
        {  // Frame 2 - Front paw up
            "   /\\_/\\    ",
            "  ( = ◡ = )  ",
            "  /_\\  /\\_ ",
            "  |_/  \\ \\ ",
            "  / \\  |_|  ",
            " /   \\ / \\ "
        },
        {  // Frame 3 - Mid stride mirrored
            "   /\\_/\\    ",
            "  ( O ‿ O )  ",
            "  / \\_\\  / ",
            "  \\ \\  \\_\\",
            "  |_|  |_|   ",
            "  / \\  / \\  "
        },
        {  // Frame 4 - Back paw up
            "   /\\_/\\    ",
            "  ( = ‿ = )  ",
            "  / \\  /_\\ ",
            "  \\ \\  |_\\",
            "  |_|  / \\  ",
            " / \\ /   \\ "
        }
    };

    // Animation loop
    for (int i = 0; i < 4; ++i) {
        for(const auto& frame : frames) {
            clearScreen();
            for(const auto& line : frame) {
                cout << line << endl;
            }
            // Calculate delay based on FPS
            this_thread::sleep_for(chrono::milliseconds(1000 / fps));
        }
    }
    return 0;
}