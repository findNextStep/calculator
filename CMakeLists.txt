project(calculator)
cmake_minimum_required(VERSION 3.5)
include_directories(
	include
)

add_library(
	CALCULATOR_lib
	src/calculator.cpp
)
add_library(
	COMPUTER_LIB
	src/computer.cpp
)
add_executable(
	${PROJECT_NAME}
	src/main.cpp
)
target_link_libraries(
	COMPUTER_LIB
	CALCULATOR_lib
)
target_link_libraries(
${PROJECT_NAME}	CALCULATOR_lib COMPUTER_LIB
)