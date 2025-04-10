#include <iostream>
#include <chrono>
#include <thread>
#include <vector>

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;


int sleeping() {
    vector<string> frame1 = {
        "          z z",
        "   /\\_/\\  ",
        "  ( o.o )  ZZZ",
        "  >  ^  <  ",
        " /   *   \\ ",
        "/_________\\ "
    };

    vector<string> frame2 = {
        "          z z",
        "   /\\_/\\  ",
        "  ( -.- )  ZZZ",
        "  >  ~  <  ",
        " /   *   \\ ",
        "/_________\\ "
    };

    for (int i = 0; i < 2; ++i) {
        clearScreen();
        
        // Draw frame 1
        for(const auto& line : frame1) {
            cout << line << endl;
        }
        sleep_for(milliseconds(1000));
        
        clearScreen();
        
        // Draw frame 2
        for(const auto& line : frame2) {
            cout << line << endl;
        }
        sleep_for(milliseconds(1000));
    }

    return 0;
}