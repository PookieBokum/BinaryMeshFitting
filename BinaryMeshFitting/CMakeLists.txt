set(name "BinaryMeshFitting")

# Gather source files
file(GLOB_RECURSE sources 
    LIST_DIRECTORIES false 
    "*.cpp"
    "*.hpp"
    "*.h"
)

# Remove any unwanted files
list(REMOVE_ITEM sources 
    "${CMAKE_CURRENT_SOURCE_DIR}/FastNoiseSIMD.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt"
)

# Create executable
add_executable(${name} ${sources})

# Set target properties
set_target_properties(${name} PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

# Include directories
target_include_directories(${name} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${OPENGL_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIRS}
)

# Link libraries
target_link_libraries(${name} PRIVATE
    OpenGL::GL
    GLEW::GLEW
    glfw
)

# Set precompiled header
target_precompile_headers(${name} PRIVATE
    <vector>
    <string>
    <memory>
    <unordered_map>
    <glm/glm.hpp>
    PCH.h
)

# Copy shaders to build directory
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
