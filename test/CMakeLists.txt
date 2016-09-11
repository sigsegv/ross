cmake_minimum_required(VERSION 3.0)

set(ROSS_UNIT_TEST_NAME ${ROSS_PROJECT_NAME}_test)

project(${ROSS_UNIT_TEST_NAME} LANGUAGES CXX)

file(GLOB HDR *.hpp)
file(GLOB SRC *.cpp)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
#set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++14")

add_executable(${ROSS_UNIT_TEST_NAME} ${SRC} ${HDR})
target_include_directories(${ROSS_UNIT_TEST_NAME}
	PUBLIC ../include
)
#set_property(TARGET ${ROSS_UNIT_TEST_NAME} PROPERTY CXX_STANDARD 14)
