add_subdirectory(sdl)
add_subdirectory(qt)
add_subdirectory(imgui)

add_subdirectory(interface)
add_subdirectory(emulation)

add_executable(
        intro
        main.cpp
)
target_link_libraries(
        intro PRIVATE
        interface
        CONAN_PKG::spdlog
)
