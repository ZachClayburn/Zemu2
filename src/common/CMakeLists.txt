add_library(common INTERFACE)

target_include_directories(
        common INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
