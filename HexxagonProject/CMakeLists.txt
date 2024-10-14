cmake_minimum_required(VERSION 3.24)
project(Hexxagon)

set(CMAKE_CXX_STANDARD 23)
set(BUILD_SHARED_LIBS FALSE)
include(FetchContent)
FetchContent_Declare(SFML GIT_REPOSITORY https://github.com/SFML/SFML.git)
FetchContent_MakeAvailable(SFML)

add_executable(Hexxagon main.cpp StartPage.cpp StartPage.h Menu.cpp Menu.h Engine.cpp Engine.h HighScopes.h)
target_link_libraries(Hexxagon PRIVATE sfml-graphics)