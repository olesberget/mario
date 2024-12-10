cmake_minimum_required(VERSION 3.20)
project(Mario)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.6.1 COMPONENTS graphics audio system window REQUIRED)

add_executable(${PROJECT_NAME} 
    src/core/main.cpp
    src/entities/Block.cpp
    src/entities/Character.cpp
    src/entities/Coin.cpp
    src/core/Game.cpp
    src/world/Map.cpp
    src/entities/Mushroom.cpp
    src/entities/QuestionBlock.cpp
    src/world/Tile.cpp
    src/utils/GameObject.cpp
)
target_include_directories(${PROJECT_NAME} PRIVATE include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/rapidjson)
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio sfml-system sfml-window)