cmake_minimum_required(VERSION 3.15)

# Project Name
project(StudentProgressTracker LANGUAGES CXX)

# C++ Standard (Using C++17 for modern features)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ==============================================================================
# 1. FETCH FLTK (AUTOMATIC DEPENDENCY DOWNLOAD)
# ==============================================================================
include(FetchContent)

message(STATUS "Checking for FLTK... (Will download if missing)")

# Configure FLTK options to speed up build and AVOID OpenGL errors
set(FLTK_BUILD_TEST OFF CACHE BOOL "" FORCE)
set(FLTK_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(FLTK_BUILD_FLUID OFF CACHE BOOL "" FORCE)
set(FLTK_BUILD_PDF OFF CACHE BOOL "" FORCE)      # Disable PDF to save time
set(FLTK_BUILD_HTML_DOCS OFF CACHE BOOL "" FORCE)

# CRITICAL: Aggressively disable OpenGL to prevent Windows SDK conflicts
set(OPTION_USE_GL OFF CACHE BOOL "" FORCE)
set(FLTK_BUILD_GL OFF CACHE BOOL "" FORCE)
set(FLTK_USE_GL OFF CACHE BOOL "" FORCE)
set(FLTK_OPENGL_SUPPORT OFF CACHE BOOL "" FORCE)
set(OPTION_BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

# Download FLTK Source
FetchContent_Declare(
    fltk
    GIT_REPOSITORY https://github.com/fltk/fltk.git
    GIT_TAG        master
)

FetchContent_MakeAvailable(fltk)

# ==============================================================================
# 2. SOURCE CODE MANAGEMENT
# ==============================================================================

# Automatically find all .cpp and .hpp files in the 'src' directory
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "src/*.hpp")

# Create the Executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Include the 'src' directory so includes like #include "App.hpp" work
target_include_directories(${PROJECT_NAME} PRIVATE src)

# ==============================================================================
# 3. LINKING
# ==============================================================================

# Link FLTK libraries to our executable
if(TARGET fltk)
    # Modern CMake target linkage (FLTK 1.4+)
    # Removed fltk_gl linkage
    target_link_libraries(${PROJECT_NAME} PRIVATE fltk fltk_images)
else()
    # Fallback for older FLTK versions
    include_directories(${FLTK_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} PRIVATE ${FLTK_LIBRARIES})
endif()

message(STATUS "Build configuration ready. Run 'cmake --build .' to compile.")