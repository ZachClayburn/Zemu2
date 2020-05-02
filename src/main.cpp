#include "MainWindow.h"
#include "GameBoy.h"
#include <stdexcept>
#include <spdlog/spdlog.h>

int main(int /*argc*/, const char ** /*argv*/) {
    try {
        auto &window = MainWindow::get();
        auto buffer = window.getScreenBuffer();
        GameBoy gameBoy(buffer);
        MainWindow::pause(1000);
    } catch (std::runtime_error &error) {
        spdlog::error(error.what());
    }
    return 0;
}
