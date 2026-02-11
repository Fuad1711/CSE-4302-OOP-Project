cmake_minimum_required(VERSION 3.10)
project(PathaoRipOff)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Include the headers directory
include_directories(include)

# 2. Find ALL .cpp files inside the src/ folder (including main.cpp)
file(GLOB_RECURSE SOURCES "src/*.cpp")

# 3. FIX for Windows "WinMain" error: Explicitly set console mode
if(WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mconsole")
endif()

# 4. Create the executable using the discovered sources
add_executable(PathaoRipOff ${SOURCES})