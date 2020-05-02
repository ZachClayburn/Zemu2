add_library(
        emulation
        GameBoy.cpp
        BootRom.cpp
        IRamBank.cpp IRamBank.h RamBank.cpp RamBank.h RamEcho.cpp RamEcho.h)

target_include_directories(
        emulation PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(
        emulation PRIVATE
        project_options
        project_warnings
        CONAN_PKG::spdlog
        interface
)