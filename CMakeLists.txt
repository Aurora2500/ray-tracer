cmake_minimum_required(VERSION 3.5)

project(App)

file(GLOB SRC "src/*.cpp")

add_executable(App ${SRC})

set_target_properties(App PROPERTIES
	CXX_STANDARD 17
	COMPILE_WARNING_AS_ERROR ON
)

add_subdirectory(glfw)
target_link_libraries(App glfw)

find_package(GLEW REQUIRED)
set(OpenGL_GL_PREFERENCE LEGACY)
find_package(OpenGL REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
include_directories(${OPENGL_INCLUDE_DIRS})
target_link_libraries(App ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES})