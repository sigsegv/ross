cmake_minimum_required(VERSION 3.0)

set(ROSS_SAMPLE_NAME ${ROSS_PROJECT_NAME}_sample)

project(${ROSS_SAMPLE_NAME} LANGUAGES CXX)

file(GLOB HDR *.hpp)
file(GLOB SRC *.cpp)

add_executable(${ROSS_SAMPLE_NAME} ${SRC} ${HDR})
target_include_directories(${ROSS_SAMPLE_NAME}
	PUBLIC ../include
)