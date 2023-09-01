cmake_minimum_required(VERSION 3.5)

add_executable(App src/main.cpp)

set_target_properties(App PROPERTIES
	CXX_STANDARD 17
	COMPILE_WARNING_AS_ERROR ON
)

add_subdirectory(glfw)
target_link_libraries(App glfw)

find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
target_link_libraries(App ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES})