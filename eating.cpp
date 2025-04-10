#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

const std::vector<std::string> FRAMES = {
    // Frame 1: Original state
    R"(
     │\__/│
    (  ◠‿◠ )
  ⎻  )───(
 ⎛ ⎛ /     \    ⎛ ⎛ ⎛
  ⎝   ⎟ │ │ │  ⎠ ⎠ ⎠
   '───' ⎻ ⎻ ⎻ ›∙∙∙◎›)",

    // Frame 2: Eating motion
    R"(
     │\__/│
    (  ◡‿◡ )
  ⎻  )───(
 ⎛ ⎛ /     \    ⎛ ⎛ ⎛
  ⎝   ⎟ │ │ │  ⎠ ⎠ ⎠
   '───' ⎻ ⎻ ⎻ ›∙∙◎›)",

    // Frame 3: Final chew
    R"(
     │\__/│
    (  ◡‿◡ )
  ⎻  )───(
 ⎛ ⎛ /     \    ⎛ ⎛ ⎛
  ⎝   ⎟ │ │ │  ⎠ ⎠ ⎠
   '───' ⎻ ⎻ ⎻ ›∙◎›)"
};

void clearScreen() {
    std::cout << "\033[2J\033[1;1H";
}

void eating() {
    for (int i = 0; i < 3; ++i) {
        clearScreen();
        std::cout << FRAMES[i] << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}
