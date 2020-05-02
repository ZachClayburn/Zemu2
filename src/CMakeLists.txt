add_subdirectory(sdl)
add_subdirectory(qt)
add_subdirectory(imgui)

add_subdirectory(common)
add_subdirectory(interface)
add_subdirectory(emulation)

add_executable(
        zemu
        main.cpp
)
target_link_libraries(
        zemu PRIVATE
        interface
        emulation
        common
        CONAN_PKG::spdlog
)
