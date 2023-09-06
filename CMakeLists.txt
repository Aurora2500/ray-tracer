cmake_minimum_required(VERSION 3.5)

project(App)

file(GLOB SRC "src/*.cpp" "src/*.hpp")
file(GLOB SRC_GA "src/genetic_algorithm/*.cpp")

add_executable(App ${SRC} "glad/src/glad.c"
	${SRC_GA}
)

set_target_properties(App PROPERTIES
	CXX_STANDARD 20
)

add_subdirectory(glfw)
add_subdirectory(glm)
target_link_libraries(App glfw)
target_link_libraries(App glm)

include_directories("glad/include")
target_link_libraries(App ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES})