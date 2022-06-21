cmake_minimum_required(VERSION 3.17)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(raylib QUIET)
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
  include(FetchContent)
  FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/refs/tags/4.0.0.tar.gz
  )
  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(raylib)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
    add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
  endif()
endif()

project(bomberman)
set (SRC
    ../Core/main.cpp
    ../Core/Errors.cpp
    ../Core/Event.cpp
    ../Core/main.cpp
    ../Core/Scene.cpp
    ../Core/SceneManager.cpp
    ../Core/Menu/Button.cpp
    ../Core/Menu/CheckBox.cpp
    ../Core/Menu/Object2D/Sprite.cpp
    ../Core/Menu/Object2D/Model2D.cpp
    ../Core/Game/Map.cpp
    ../Core/Game/Object3D/BlockD.cpp
    ../Core/Game/Object3D/BlockI.cpp
    ../Core/Game/Object3D/Bomb.cpp
    ../Core/Game/Object3D/Bonus.cpp
    ../Core/Game/Object3D/Character.cpp
    ../Core/Game/Object3D/IA.cpp
    ../Core/Game/Object3D/Model3D.cpp
    ../Core/Game/Object3D/Mesh.cpp
    ../Core/Game/Object3D/Fire.cpp
    ../Music/IMusic.cpp
    ../Music/ISound.cpp
)
add_executable(bomberman
    ${SRC}
)

target_include_directories(bomberman PUBLIC ${CMAKE_SOURCE_DIR})
include_directories(RAYLIB/src)
target_link_libraries(bomberman raylib)
