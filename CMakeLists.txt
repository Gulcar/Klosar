cmake_minimum_required(VERSION 3.16)

project(Klosar)

add_executable(${PROJECT_NAME}
	src/Main.cpp
	libs/glad-3.3-core/src/glad.c
)

add_subdirectory(libs/glfw-3.3.8)

target_include_directories(${PROJECT_NAME} PRIVATE
	libs/glfw-3.3.8/include
	libs/glm-0.9.9.8/
	libs/glad-3.3-core/include
)

target_link_libraries(${PROJECT_NAME} PRIVATE
	glfw
)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)
