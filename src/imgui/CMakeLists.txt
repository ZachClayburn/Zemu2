# imgui test executable, with full warnings enabled
add_library(imgui_impl STATIC
        imgui_impl_opengl3.cpp imgui_impl_opengl3.h
        imgui_impl_sdl.cpp imgui_impl_sdl.h)

target_link_libraries(imgui_impl PUBLIC
        CONAN_PKG::imgui
        CONAN_PKG::sdl2)
target_link_libraries(imgui_impl PRIVATE
        project_options)

add_executable(test_imgui test.cpp)
target_link_libraries(test_imgui PRIVATE
        project_warnings
        project_options
        imgui_impl
        CONAN_PKG::glew
        CONAN_PKG::spdlog)

