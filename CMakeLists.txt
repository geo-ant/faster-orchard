project(orchard LANGUAGES CXX)
include(CheckCXXCompilerFlag)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(orchard 
  src/main.cpp
  src/game.cpp
  src/strategies.cpp)


# check_cxx_compiler_flag("-Ofast" COMPILER_SUPPORTS_OFAST)
# check_cxx_compiler_flag("-march=native" COMPILER_SUPPORTS_MARCH_NATIVE)
# if(COMPILER_SUPPORTS_MARCH_NATIVE)
#   target_compile_options(orchard PUBLIC -march=native)
# endif()
# if(COMPILER_SUPPORTS_OFAST)
#   target_compile_options(orchard PUBLIC -Ofast)
# endif()
