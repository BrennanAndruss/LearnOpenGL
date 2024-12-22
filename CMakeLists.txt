cmake_minimum_required(VERSION 3.10)
project(LearnOpenGL)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add the GLFW submodule directory to the include path
add_subdirectory(ext/glfw)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Use glob to get the list of all source files
file(GLOB_RECURSE SOURCES
	"${CMAKE_SOURCE_DIR}/src/*.cpp"
	"${CMAKE_SOURCE_DIR}/ext/glad/src/*.c"
)

# Include header and resource files for IDE support
file(GLOB_RECURSE HEADERS "src/*.h" "ext/glad/*/*.h")
file(GLOB_RECURSE GLSL "resources/*.vert" "resources/*.frag")

# Include directories for headers
include_directories("ext")
include_directories("ext/glad/include")

# Set the executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${GLSL})

# Link libraries for the project
target_link_libraries(${PROJECT_NAME} PRIVATE
	glfw
	${OPENGL_LIBRARIES}
)

