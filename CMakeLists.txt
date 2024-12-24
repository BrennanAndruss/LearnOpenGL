cmake_minimum_required(VERSION 3.10)
project(LearnOpenGL)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add submodule directories to the include path
add_subdirectory(ext/glfw)
add_subdirectory(ext/glm)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Use glob to get the list of all source files
file(GLOB_RECURSE SOURCES
	"${CMAKE_SOURCE_DIR}/src/*.cpp"
	"${CMAKE_SOURCE_DIR}/ext/glad/src/*.c"
)

# Collect header and resource files for IDE support
file(GLOB_RECURSE HEADERS "src/*.h" "ext/stb/*.h" "ext/glad/*/*.h")
source_group("Header Files" FILES ${HEADERS})

file(GLOB_RECURSE RESOURCES  "resources/*.vert" "resources/*.frag")
source_group("Resource Files" FILES ${RESOURCES})

# Include directories for headers
include_directories("ext")
include_directories("ext/glad/include")

# Set the executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${RESOURCES})

# Link libraries for the project
target_link_libraries(${PROJECT_NAME} PRIVATE
	glfw
	glm
	${OPENGL_LIBRARIES}
)

