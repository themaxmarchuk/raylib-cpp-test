cmake_minimum_required(VERSION 3.11)
project(raylib-cpp-test)

# Configure raylib
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)

# Build raylib
add_subdirectory(vendor/raylib)

# Add the main entry point
add_executable(${PROJECT_NAME} main.cpp)

# Link raylib
target_link_libraries(${PROJECT_NAME} raylib)

