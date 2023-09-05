cmake_minimum_required(VERSION 3.5)

project(App)

file(GLOB SRC "src/*.cpp")

add_executable(App ${SRC} "glad/src/glad.c")

set_target_properties(App PROPERTIES
	CXX_STANDARD 20
)

add_subdirectory(glfw)
target_link_libraries(App glfw)

include_directories("glad/include")
target_link_libraries(App ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES})