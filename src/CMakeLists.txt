add_subdirectory(sdl)
add_subdirectory(qt)
add_subdirectory(imgui)

# Generic test that uses conan libs
add_executable(intro
        main.cpp
        Screen.cpp
        Screen.h)
target_link_libraries(
        intro PRIVATE
        project_options
        project_warnings
        CONAN_PKG::docopt.cpp
        CONAN_PKG::fmt
        CONAN_PKG::spdlog
        CONAN_PKG::sdl2
)
