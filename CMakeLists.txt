project(calculator)
cmake_minimum_required(VERSION 3.5)
include_directories(
	include
)

add_library(
	CALCULATOR_lib
	src/calculator.cpp
)

add_executable(
	${PROJECT_NAME}
	src/main.cpp
)
target_link_libraries(
${PROJECT_NAME}	CALCULATOR_lib
)