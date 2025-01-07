cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(PhysicsSim VERSION 1.0)

# Set C++ standard (you can use 14, 17, etc. based on your preference)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the SFML directory to the root of the SFML folder
set(SFML_DIR "SFML")

# Manually set SFML include and lib directories
set(SFML_INCLUDE_DIR "${SFML_DIR}/include")
set(SFML_LIB_DIR "${SFML_DIR}/lib")

# Add the SFML include directory
include_directories(${SFML_INCLUDE_DIR})

# Add your source files here
set(SOURCES
    src/SFML_Project_1.cpp
)

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link SFML libraries manually (check if these libraries are correct for SFML 3.0)
target_link_libraries(${PROJECT_NAME} 
    "${SFML_LIB_DIR}/sfml-graphics-d.lib"
    "${SFML_LIB_DIR}/sfml-window-d.lib"
    "${SFML_LIB_DIR}/sfml-system-d.lib"
)

# Optionally, you can include the bin folder to find SFML DLLs at runtime (for Windows)
set(SFML_BIN_DIR "${SFML_DIR}/bin")
set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${SFML_BIN_DIR}"
)

# Optional: Add a custom compilation flag to enable debug symbols
set(CMAKE_BUILD_TYPE Debug)
