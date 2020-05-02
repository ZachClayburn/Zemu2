#include "Screen.h"
#include <stdexcept>
#include <spdlog/spdlog.h>

int main(int /*argc*/, const char ** /*argv*/) {
    try {
        Screen::get();
        Screen::pause(1000);
    } catch (std::runtime_error &error) {
        spdlog::error(error.what());
    }
    return 0;
}
