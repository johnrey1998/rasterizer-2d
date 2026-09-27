cmake_minimum_required(VERSION 3.20)
project(Rasterizer2D CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-3.2.0
)
FetchContent_MakeAvailable(SDL3)

include_directories(include)

add_executable(rasterizer
    src/main.cpp
    src/core/core.cpp
    src/platform/platform.cpp
    src/math/vector2.cpp
    src/math/vector3.cpp
    src/math/matrix3.cpp
    src/math/color.cpp
    src/renderer/rasterizer.cpp
    src/renderer/line.cpp
    src/renderer/triangle.cpp
    src/renderer/texture.cpp
)

target_link_libraries(rasterizer PRIVATE SDL3::SDL3)

add_custom_command(TARGET rasterizer POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_newer
        $<TARGET_RUNTIME_DLLS:rasterizer>
        $<TARGET_FILE_DIR:rasterizer>
    COMMAND_EXPAND_LISTS
)

add_executable(test_math
    tests/test_math.cpp
    src/math/vector2.cpp
    src/math/vector3.cpp
    src/math/matrix3.cpp
    src/math/color.cpp
)