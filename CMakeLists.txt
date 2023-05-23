project(orchard LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(orchard 
  src/main.cpp
  src/game.cpp
  src/strategies.cpp)
