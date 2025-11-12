cmake_minimum_required(VERSION 3.16)
project(TextEditorProject LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_COMPILER g++)

# Find SDL2 and SDL2_ttf
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2TTF REQUIRED SDL2_ttf)
pkg_check_modules(SDL2GFX REQUIRED SDL2_gfx)
pkg_check_modules(SDL2IMG REQUIRED SDL2_image)

#find_package(sdl2 REQUIRED)
#find_package(sdl2_ttf REQUIRED)

add_executable(TextEditor
    src/main.cpp
)

target_include_directories(TextEditor PRIVATE
    ${SDL2_INCLUDE_DIRS}
    ${SDL2TTF_INCLUDE_DIRS}
    ${SDL2GFX_INCLUDE_DIRS}
    ${SDL2IMG_INCLUDE_DIRS}
)

target_link_libraries(TextEditor PRIVATE
    ${SDL2_LIBRARIES}
    ${SDL2TTF_LIBRARIES}
    ${SDL2GFX_LIBRARIES}
    ${SDL2IMG_LIBRARIES}
)
